/*
 * Square matrix multiplication
 * A[N][N] * B[N][N] = C[N][N]
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include <sys/timeb.h>
#include <omp.h>

/* read timer in second */
double read_timer()
{
    struct timeb tm;
    ftime(&tm);
    return (double) tm.time + (double) tm.millitm / 1000.0;
}

/* read timer in ms */
double read_timer_ms()
{
    struct timeb tm;
    ftime(&tm);
    return (double) tm.time * 1000.0 + (double) tm.millitm;
}

#define REAL float

void init(int N, REAL A[][N])
{
    int i, j;

    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
            A[i][j] = (REAL) drand48();
        }
    }
}

double maxerror(int N, REAL A[][N], REAL B[][N])
{
    int i, j;
    double error = 0.0;

    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
            double diff = (A[i][j] - B[i][j]) / A[i][j];
            if (diff < 0)
                diff = -diff;
            if (diff > error)
                error = diff;
        }
    }
    return error;
}

void matmul_base(int N, REAL A[][N], REAL B[][N], REAL C[][N]);

void matmul_base_sub(int i_start, int j_start, int Mt, int Nt, int N, REAL A[][N], REAL B[][N], REAL C[][N]);

void matmul_row1D_dist(int N, REAL A[][N], REAL B[][N], REAL C[][N], int num_tasks);

void matmul_column1D_dist(int N, REAL A[][N], REAL B[][N], REAL C[][N], int num_tasks);

void matmul_rowcol2D_dist(int N, REAL A[][N], REAL B[][N], REAL C[][N], int num_tasks_row, int num_tasks_col);

int main(int argc, char *argv[])
{
    int N;
    int num_tasks = 4; /* 4 is default number of tasks */
    double elapsed_base, elapsed_row1D_dist, elapsed_column1D_dist, elapsed_rowcol2D_dist; /* for timing */
    if (argc < 2) {
        fprintf(stderr, "Usage: matmul <n> [<#tasks(%d)>]\n", num_tasks);
        exit(1);
    }
    N = atoi(argv[1]);
    if (argc > 2) num_tasks = atoi(argv[2]);
    REAL A[N][N];
    REAL B[N][N];
    REAL C_base[N][N];
    REAL C_row1D_dist[N][N];
    REAL C_column1D_dist[N][N];
    REAL C_rowcol2D_dist[N][N];

    srand48(1 << 12);
    init(N, A);
    init(N, B);

    /* example run */
    elapsed_base = read_timer();
    matmul_base(N, A, B, C_base);
    elapsed_base = (read_timer() - elapsed_base);

    elapsed_row1D_dist = read_timer();
    matmul_row1D_dist(N, A, B, C_row1D_dist, num_tasks);
    elapsed_row1D_dist = (read_timer() - elapsed_row1D_dist);

    elapsed_column1D_dist = read_timer();
    matmul_column1D_dist(N, A, B, C_column1D_dist, num_tasks);
    elapsed_column1D_dist = (read_timer() - elapsed_column1D_dist);

    elapsed_rowcol2D_dist = read_timer();
    matmul_rowcol2D_dist(N, A, B, C_rowcol2D_dist, num_tasks, num_tasks);
    elapsed_rowcol2D_dist = (read_timer() - elapsed_rowcol2D_dist);
    /* you should add the call to each function and time the execution */

    printf("======================================================================================================\n");
    printf("\tMatrix Multiplication: A[N][N] * B[N][N] = C[N][N], N=%d\n", N);
    printf("------------------------------------------------------------------------------------------------------\n");
    printf("Performance:\t\tRuntime (ms)\t MFLOPS \t\tError (compared to base)\n");
    printf("------------------------------------------------------------------------------------------------------\n");
    printf("matmul_base:\t\t%4f\t%4f \t\t%g\n", elapsed_base * 1.0e3, ((((2.0 * N) * N) * N) / (1.0e6 * elapsed_base)),
           maxerror(N, C_base, C_base));
    printf("matmul_row1D_dist:\t%4f\t%4f \t\t%g\n", elapsed_row1D_dist * 1.0e3,
           ((((2.0 * N) * N) * N) / (1.0e6 * elapsed_row1D_dist)), maxerror(N, C_base, C_row1D_dist));
    printf("matmul_column1D_dist:\t%4f\t%4f \t\t%g\n", elapsed_column1D_dist * 1.0e3,
           ((((2.0 * N) * N) * N) / (1.0e6 * elapsed_column1D_dist)), maxerror(N, C_base, C_column1D_dist));
    printf("matmul_rowcol2D_dist:\t%4f\t%4f \t\t%g\n", elapsed_rowcol2D_dist * 1.0e3,
           ((((2.0 * N) * N) * N) / (1.0e6 * elapsed_rowcol2D_dist)), maxerror(N, C_base, C_rowcol2D_dist));
    return 0;
}

void matmul_base(int N, REAL A[][N], REAL B[][N], REAL C[][N])
{

    int i, j, k;
    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
            C[i][j] = 0;
            for (k = 0; k < N; k++)
                C[i][j] += A[i][k] * B[k][j];
        }
    }
}

/* compute submatrix multiplication, A[start:length] notation
 * A[i_start:Mt][N] x B[N][j_start:Nt] = C[i_start:Mt][j_start:Nt]
 */
void matmul_base_sub(int i_start, int j_start, int Mt, int Nt, int N,
                     REAL A[][N], REAL B[][N], REAL C[][N])
{
    int i, j, k;
    for (i = i_start; i < Mt + i_start; i++) {
        for (j = j_start; j < Nt + j_start; j++) {
            C[i][j] = 0;
            for (k = 0; k < N; k++)
                C[i][j] += A[i][k] * B[k][j];
        }
    }
}

/* this is a sequential verion showing the decomposition */
void matmul_row1D_dist_seq(int N, REAL A[][N], REAL B[][N], REAL C[][N], int num_tasks)
{
    int tid;
    for (tid = 0; tid < num_tasks; tid++) {
        int i_start, j_start;
        int Mt, Nt;
        Mt = N / num_tasks;
        Nt = N;
        i_start = tid * Mt;
        j_start = 0;
        matmul_base_sub(i_start, j_start, Mt, Nt, N, A, B, C);
    }
}

void matmul_row1D_dist(int N, REAL A[][N], REAL B[][N], REAL C[][N], int num_tasks)
{
#pragma omp parallel num_threads(num_tasks)
    {
        int tid = omp_get_thread_num();
        int i_start, j_start;
        int Mt, Nt;
        Mt = N / num_tasks;
        Nt = N;
        i_start = tid * Mt;
        j_start = 0;
        matmul_base_sub(i_start, j_start, Mt, Nt, N, A, B, C);
    }
}

void matmul_column1D_dist(int N, REAL A[][N], REAL B[][N], REAL C[][N], int num_tasks)
{
#pragma omp parallel num_threads(num_tasks)
    {
        int tid = omp_get_thread_num();
        int i_start, j_start;
        int Mt, Nt;
        Mt = N;
        Nt = N / num_tasks;
        i_start = 0;
        j_start = tid * Nt;
        matmul_base_sub(i_start, j_start, Mt, Nt, N, A, B, C);
    }
}

void matmul_rowcol2D_dist(int N, REAL A[][N], REAL B[][N], REAL C[][N], int num_tasks_row, int num_tasks_col)
{
#pragma omp parallel num_threads(num_tasks_row + num_tasks_col)
    {
        int tid = omp_get_thread_num();
        int i_start, j_start;
        int Mt, Nt;
        Mt = N / num_tasks_row;
        Nt = N / num_tasks_col;
        i_start = tid * Mt;
        j_start = tid * Nt;
        matmul_base_sub(i_start, j_start, Mt, Nt, N, A, B, C);
    }
}
