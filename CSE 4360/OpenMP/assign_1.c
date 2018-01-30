//
// Created by nick on 1/30/18.
//
#include "limits.h"
#include "stdio.h"
#include "stdlib.h"
#include "time.h"

#include "omp.h"

#include <sys/time.h>

// gets the current time in seconds with microsecond precision
double get_time()
{
    struct timeval t;
    struct timezone tzp;
    gettimeofday(&t, &tzp);
    return t.tv_sec + t.tv_usec*1e-6;
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
    for (int j = 0; j < N; j++)
    {
        for (int i = 0; i < N; i++)
        {
            printf("%d\t", matrix[i][j]);
        }
        printf("\n");
    }
}

// Testing macro used so that the main void doesn't have so much clutter

#define PERFORM_TEST_MAX(function) \
    initialClock = get_time(); \
    max = function(N, matrix); \
    executionTime = (get_time() - initialClock) * 1000.f; \
    printf("Found the max for %s: %d in %.2f ms\n", #function, max, executionTime);


int find_matrix_max_s(int N, int matrix[N][N]);
void fill_bins_s(int N, int M, int matrix[N][N], int bins[10]);

// Parallel 1: Manual decomposition
int find_matrix_max_p1(int N, int matrix[N][N]);
void fill_bins_p1();

// Parallel 2: Use "for" construct without "reduction" clause
int find_matrix_max_p2(int N, int matrix[N][N]);
void fill_bins_p2();

// Parallel 3: Use "for" construct with "reduction" clause
int find_matrix_max_p3(int N, int matrix[N][N]);
void fill_bins_p3();


int main(int argc, char *argv[])
{
    if (argc < 3) {
        fprintf(stderr, "Usage: assign_1 <num elems> <max elem> \n");
        exit(1);
    }
    // Gather the size of matrix (N) and max possible value (M)
    int N = atoi(argv[1]);
    int M = atoi(argv[2]);
    // Setup random generator
    srand(time(NULL));
    // Generate the matrix and bins array
    int (*matrix)[N] = malloc(sizeof(int[N][N]));
    int bins[10];
    init(N, M, matrix);

    //print_matrix(N, matrix);

    // Things used by the macro
    double initialClock, executionTime; // used for timing
    int max; // used for storing the max


    // Perform the "find the max" tests
    PERFORM_TEST_MAX(find_matrix_max_s);

    PERFORM_TEST_MAX(find_matrix_max_p1);

    PERFORM_TEST_MAX(find_matrix_max_p2);

    PERFORM_TEST_MAX(find_matrix_max_p3);

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

void fill_bins_s(int N, int M, int matrix[N][N], int bins[10])
{
    // The idea for the bins is to have the output array (fixed size 10)
    // keep track of the count for each index. Each index is calculated
    // as given in the assignment instructions with
    //

    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {

            // Determine the index of the given matrix integer value
            int indx;

            bins[indx] += 1;

        }

    }

}


// Parallel-1
int find_matrix_max_p1(int N, int matrix[N][N])
{
    int toReturn = INT_MIN;

    int num_threads;

    #pragma omp parallel shared(matrix)
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
            for (j = start; j < end; j++)
                if (matrix[i][j] > toReturn)
                    #pragma omp critical
                    toReturn = matrix[i][j];
    };

    return toReturn;
}



// Parallel-2
int find_matrix_max_p2(int N, int matrix[N][N])
{
    int toReturn = INT_MIN;

    #pragma omp parallel for
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            if (matrix[i][j] > toReturn)
            {
                toReturn = matrix[i][j];
            }

    return toReturn;
}


// Parallel-3
int find_matrix_max_p3(int N, int matrix[N][N])
{
    int toReturn = INT_MIN;

    #pragma omp parallel for reduction(max:toReturn)
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            if (matrix[i][j] > toReturn)
            {
                toReturn = matrix[i][j];
            }

    return toReturn;
}