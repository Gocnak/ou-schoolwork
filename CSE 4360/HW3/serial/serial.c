//
// Created by nick on 4/3/18.
//

#include <memory.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/time.h>
typedef enum
{
    MAT_TL = 0, // Top left
    MAT_TR = 1, // Top right
    MAT_BL = 2, // Bottom left
    MAT_BR = 3 // Bottom right
} MAT_POS;

void findStart(int N, MAT_POS pos, int *i, int *j, int *i_end, int *j_end)
{
    int isTop = (pos < MAT_BL);
    int isRight = (pos % 2 == 1);

    *i = (isTop) ? 0 : N/2;
    *j = (isRight) ? N/2 : 0;
    *i_end = (isTop) ? N/2 : N;
    *j_end = (isRight) ? N : N/2;
}
// gets the current time in seconds with microsecond precision
double get_time()
{
    struct timeval t;
    struct timezone tzp;
    gettimeofday(&t, &tzp);
    return t.tv_sec + t.tv_usec * 1e-6;
}

void fillIdentity(int N, float *matrix, MAT_POS pos, float scalar)
{
    int i_start, j_start, i_end, j_end;
    findStart(N, pos, &i_start, &j_start, &i_end, &j_end);
    for (int i = i_start; i < i_end; i++)
    {
        for (int j = j_start; j < j_end; j++)
        {
            matrix[i*N+j] = (i == j) ? (scalar) : 0.0f;
        }
    }
}

void fillZeros(int N, float *matrix, MAT_POS pos)
{
    int i_start, j_start, i_end, j_end;
    findStart(N, pos, &i_start, &j_start, &i_end, &j_end);
    for (int i = i_start; i < i_end; i++)
    {
        for (int j = j_start; j < j_end; j++)
        {
            matrix[i*N+j] = 0.0f;
        }
    }
}

void fillRand(int N, float *matrix, MAT_POS pos, float scalar)
{
    int i_start, j_start, i_end, j_end;
    findStart(N, pos, &i_start, &j_start, &i_end, &j_end);
    for (int i = i_start; i < i_end; i++)
    {
        for (int j = j_start; j < j_end; j++)
        {
            matrix[i*N+j] = scalar * (rand() / (float)RAND_MAX);
        }
    }
}


//Assuming NxN matricies
void matMul(int N, const float *matrix1, const float *matrix2, float *result)
{
    int sqr = N*N;
    memset(result, 0, sqr * sizeof(float));

    for (int ijk = 0; ijk < sqr; ijk++)
    {
        int i = ijk / N;
        int j = (ijk / N) % N;
        int k = ijk % N;
        result[i*N+j] += matrix1[i*N+k] * matrix2[k*N+j];
    }
}

#define fabs(val) (val) < 0.0f ? (-(val)) : (val)

float mat_diff(int N, const float *matrix1, const float *matrix2)
{
    float diff = 0.0f;
    for (int ij = 0; ij < (N*N); ij++)
    {
        int i = ij / N;
        int j = (ij / N) % N;
        diff += fabs(matrix1[i*N+j] - matrix2[i*N+j]);
    }
    return diff;
}

void printMatrix(int N, float *matrix)
{
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            printf("%.1f ", matrix[i*N+j]);
        }
        printf("\n");
    }
}

float rothVerf_serial(int N)
{
    int extent = 2*N;
    float *matrix_1 = (float*)malloc(extent*extent*sizeof(float));
    float *matrix_2 = (float*)malloc(extent*extent*sizeof(float));
    float *result = (float*)malloc(extent*extent*sizeof(float));

    srand(100);

    fillIdentity(extent, matrix_1, MAT_TL, 1.0f);
    fillRand(extent, matrix_1, MAT_TR, 1.0f);
    fillZeros(extent, matrix_1, MAT_BL);
    fillIdentity(extent, matrix_1, MAT_BR, 1.0f);

    fillIdentity(extent, matrix_2, MAT_TL, 1.0f);
    fillRand(extent, matrix_2, MAT_TR, 2.0f);
    fillZeros(extent, matrix_2, MAT_BL);
    fillIdentity(extent, matrix_2, MAT_BR, -1.0f);

    // Multiply these two
    matMul(extent, matrix_1, matrix_2, result);

    // Re-use matrix_1 for last matrix
    fillIdentity(extent, matrix_1, MAT_TL, 1.0f);
    fillRand(extent, matrix_1, MAT_TR, -1.0f);
    fillZeros(extent, matrix_1, MAT_BL);
    fillIdentity(extent, matrix_1, MAT_BR, 1.0f);

    // Multiply result * matrix_1 into matrix_2
    matMul(extent, result, matrix_1, matrix_2);

    // Re-use result for RHS matrix
    fillIdentity(extent, result, MAT_TL, 1.0f);
    fillZeros(extent, result, MAT_TR);
    fillZeros(extent, result, MAT_BL);
    fillIdentity(extent, result, MAT_BR, -1.0f);

    // Compare matrix_2 and result
    /*printf("LHS:\n");
    printMatrix(N, matrix_2);
    printf("RHS:\n");
    printMatrix(N, result);*/
    float diff = mat_diff(N, matrix_2, result);

    free(matrix_1);
    free(matrix_2);
    free(result);

    return diff;
}

int main(int argc, char **argv)
{
    int N = 5000;
    if (argc > 1)
        N = atoi(argv[1]);

    printf("Calculating serial with N=%d\n", N);

    double start = get_time();
    float diffSerial = rothVerf_serial(N);
    printf("Serial diff: %.1f\n in time %.3f ms", diffSerial, (get_time() - start) * 1000.0f);
    return 0;
}