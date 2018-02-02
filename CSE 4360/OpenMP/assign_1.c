//
// Created by nick on 1/30/18.
//
#include "limits.h"
#include "stdio.h"
#include "stdlib.h"
#include "memory.h"
#include "omp.h"
#include <sys/time.h>

// ======== Defines for the entire project =========
// Getting the value of the macro as a string
#define STR(name) #name
#define MACRO_VALUE(name) STR(name)

// Define the number of histogram bins here
#define HIST_BINS 10

// Define the number of threads to use
#define THREADS 12

// Define the chunk size
#define CHUNK 8

// Define the scheduling type
#define SCHED_TYPE dynamic

// Define the scheduling to use
#define SCHEDULE schedule(SCHED_TYPE, CHUNK)

// Define the scheduling value as a string
#define SCHED_VALUE MACRO_VALUE(SCHEDULE)

// Const defines for when no parameters are given
const int N_global = 10000;
const int M_global = 1000;

// gets the current time in seconds with microsecond precision
double get_time()
{
    struct timeval t;
    struct timezone tzp;
    gettimeofday(&t, &tzp);
    return t.tv_sec + t.tv_usec * 1e-6;
}


// Initializes a matrix of size NxN with values of [0, M)
void init(int N, int M, int A[N][N])
{
    int i, j;

    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
            A[i][j] = rand() % M;
        }
    }
}

// Prints every value inside of a matrix
void print_matrix(int N, int matrix[N][N])
{
    for (int j = 0; j < N; j++) {
        for (int i = 0; i < N; i++) {
            printf("%d\t", matrix[i][j]);
        }
        printf("\n");
    }
}

// Prints every value inside of a histogram
void print_histogram(int hist[])
{
    int sum = 0;
    for (int i = 0; i < HIST_BINS; i++) {
        sum += hist[i];
        printf("%d\t", hist[i]);
    }
    printf("Sum: %d\n", sum);
}

// Testing macros used so that the main void doesn't have so much clutter
#define PERFORM_TEST_MAX(function) \
    initialClock = get_time(); \
    max = function(N, matrix); \
    executionTime = (get_time() - initialClock) * 1000.f; \
    printf("Found the max for %s: %d in %.2f ms\n", #function, max, executionTime);

#define PERFORM_TEST_BINS(function) \
    initialClock = get_time(); \
    function(N, M, hist, matrix); \
    executionTime = (get_time() - initialClock) * 1000.0f; \
    printf("Created the histogram with %s in %.2f ms\n", #function, executionTime); \
    print_histogram(hist); \
    memset(hist, 0, sizeof(hist));

// Serial: No parallel at all, just brute force it on one thread
int find_matrix_max_s(int N, int matrix[N][N]);
void fill_bins_s(int N, int M, int hist[], int matrix[N][N]);

// Parallel 1: Manual decomposition
int find_matrix_max_p1(int N, int matrix[N][N]);
void fill_bins_p1(int N, int M, int hist[], int matrix[N][N]);

// Parallel 2: Use "for" construct without "reduction" clause
int find_matrix_max_p2(int N, int matrix[N][N]);
void fill_bins_p2(int N, int M, int hist[], int matrix[N][N]);

// Parallel 3: Use "for" construct with "reduction" clause
int find_matrix_max_p3(int N, int matrix[N][N]);
void fill_bins_p3(int N, int M, int hist[], int matrix[N][N]);


int main(int argc, char *argv[])
{
    int N, M;
    // Gather the size of matrix (N) and max possible value (M)
    if (argc < 3) {
        // Use the globals when the arguments weren't passed right
        N = N_global;
        M = M_global;
    }
    else {
        N = atoi(argv[1]);
        M = atoi(argv[2]);
    }
    
    // Setup random generator
    srand(1 << 12);
    // Generate the matrix
    int (*matrix)[N] = malloc(sizeof(int[N][N]));
    init(N, M, matrix);
    // Create the histogram array
    int hist[HIST_BINS];
    memset(hist, 0, sizeof(hist));

    //print_matrix(N, matrix);

    // Things used by the macro
    double initialClock, executionTime; // used for timing
    int max; // used for storing the max

    printf("Running the tests with %d thread(s) and %s\n", THREADS, SCHED_VALUE);

    // Perform the "find the max" tests
    PERFORM_TEST_MAX(find_matrix_max_s);

    PERFORM_TEST_MAX(find_matrix_max_p1);

    PERFORM_TEST_MAX(find_matrix_max_p2);

    PERFORM_TEST_MAX(find_matrix_max_p3);

    // Perform the histogram tests
    PERFORM_TEST_BINS(fill_bins_s);

    PERFORM_TEST_BINS(fill_bins_p1);

    PERFORM_TEST_BINS(fill_bins_p2);

    PERFORM_TEST_BINS(fill_bins_p3);

    return 0;
}


// ============= Implementations =================
// Serial
int find_matrix_max_s(int N, int matrix[N][N])
{
    int toReturn = INT_MIN;
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            if (matrix[i][j] > toReturn) toReturn = matrix[i][j];

    return toReturn;
}

void fill_bins_s(int N, int M, int hist[], int matrix[N][N])
{
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            // Loop over bin indices
            for (int k = 0; k < HIST_BINS; k++) {
                int candidate = matrix[i][j];
                if (k * M / HIST_BINS <= candidate && candidate < (k + 1) * M / HIST_BINS) {
                    hist[k]++;
                    break;
                }
            }
        }
    }
}


// Parallel-1
int find_matrix_max_p1(int N, int matrix[N][N])
{
    int toReturn = INT_MIN;

    int num_threads;

    #pragma omp parallel shared(matrix) num_threads(THREADS)
    {
        int i, j, start, end;

        #pragma omp single
        {
            num_threads = omp_get_num_threads();
        }

        int pID = omp_get_thread_num();

        start = pID * N / num_threads;
        end = ((pID + 1) * N) / num_threads;

        for (i = start; i < end; i++)
            for (j = 0; j < N; j++)
                if (matrix[i][j] > toReturn)
                    #pragma omp critical
                    toReturn = matrix[i][j];
    };

    return toReturn;
}

void fill_bins_p1(int N, int M, int hist[], int matrix[N][N])
{
    int num_threads;

    #pragma omp parallel num_threads(THREADS)
    {
        int i, j, start, end;

        int local_hist[HIST_BINS];
        memset(local_hist, 0, sizeof(local_hist));

        #pragma omp single
        {
            num_threads = omp_get_num_threads();
        }

        int pID = omp_get_thread_num();

        start = pID * N / num_threads;
        end = ((pID + 1) * N) / num_threads;

        for (i = start; i < end; i++) {
            for (j = 0; j < N; j++) {
                // Loop over bin indices
                for (int k = 0; k < HIST_BINS; k++) {
                    int candidate = matrix[i][j];
                    if (k * M / HIST_BINS <= candidate && candidate < (k + 1) * M / HIST_BINS) {
                        local_hist[k]++;
                        break;
                    }
                }
            }
        }

        #pragma omp critical
        for (i = 0; i < HIST_BINS; i++)
        {
            hist[i] += local_hist[i];
        }
    };
}


// Parallel-2
int find_matrix_max_p2(int N, int matrix[N][N])
{
    int toReturn = INT_MIN;

    #pragma omp parallel for num_threads(THREADS) SCHEDULE
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            if (matrix[i][j] > toReturn)
                toReturn = matrix[i][j];

    return toReturn;
}

void fill_bins_p2(int N, int M, int hist[], int matrix[N][N])
{
    #pragma omp parallel num_threads(THREADS)
    {
        int local_bins[HIST_BINS];
        memset(local_bins, 0, sizeof(local_bins));

        #pragma omp for nowait SCHEDULE
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                // Loop over bin indices
                for (int k = 0; k < HIST_BINS; k++) {
                    int candidate = matrix[i][j];
                    if (k * M / HIST_BINS <= candidate && candidate < (k + 1) * M / HIST_BINS) {
                        local_bins[k]++;
                        break;
                    }
                }
            }
        }

        #pragma omp critical
        for (int i = 0; i < HIST_BINS; i++)
        {
            hist[i] += local_bins[i];
        }
    };
}

// Parallel-3
int find_matrix_max_p3(int N, int matrix[N][N])
{
    int toReturn = INT_MIN;

    #pragma omp parallel for reduction(max:toReturn) num_threads(THREADS) SCHEDULE
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            if (matrix[i][j] > toReturn)
                toReturn = matrix[i][j];

    return toReturn;
}

void fill_bins_p3(int N, int M, int hist[], int matrix[N][N])
{
    #pragma omp parallel for reduction(+:hist[:HIST_BINS]) num_threads(THREADS) SCHEDULE
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            // Loop over bin indices
            for (int k = 0; k < HIST_BINS; k++) {
                int candidate = matrix[i][j];
                if (k * M / HIST_BINS <= candidate && candidate < (k + 1) * M / HIST_BINS) {
                    hist[k]++;
                    break;
                }
            }
        }
    }
}