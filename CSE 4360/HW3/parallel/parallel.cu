//
// Created by nick on 4/3/18.
//
#include "cuda.h"
#include "parallel.h"
#include <stdio.h>
#include <host_defines.h>
#include <device_launch_parameters.h>
#include <cuda_runtime.h>
#include <sys/time.h>

#define TILE_DIM 32

__global__ void coalescedMultiply(float *a, float *b, float *c, int N)
{
    int row = blockIdx.y * blockDim.y + threadIdx.y;
    int col = blockIdx.x * blockDim.x + threadIdx.x;
    float sum = 0.0f;
    for (int i = 0; i < TILE_DIM; i++) {
        sum += a[row*TILE_DIM+i] * b[i*N+col];
    }
    c[row*N+col] = sum;
    /*__shared__ float aTile[TILE_DIM][TILE_DIM], bTile[TILE_DIM][TILE_DIM];

    int row = blockIdx.y * blockDim.y + threadIdx.y;
    int col = blockIdx.x * blockDim.x + threadIdx.x;
    float sum = 0.0f;
    aTile[threadIdx.y][threadIdx.x] = a[row*TILE_DIM+threadIdx.x];
    bTile[threadIdx.y][threadIdx.x] = b[threadIdx.y*N+col];
    __syncthreads();
    for (int i = 0; i < TILE_DIM; i++)
    {
        sum += aTile[threadIdx.y][i] * bTile[i][threadIdx.x];
    }
    c[row*N+col] = sum;*/
}

static void HandleError( cudaError_t err,
                         const char *file,
                         int line ) {
    if (err != cudaSuccess) {
        printf( "%s in %s at line %d\n", cudaGetErrorString( err ),
                file, line );
        exit( EXIT_FAILURE );
    }
}
#define HANDLE_ERROR( err ) (HandleError( err, __FILE__, __LINE__ ))

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

#define fabs(val) (val) < 0.0f ? (-(val)) : (val)

float mat_diff(int N, float *matrix1, float *matrix2)
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

void printMa(int N, float *matrix)
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

float rothVerf_parallel(int ext)
{
    int N = ext*2;
    // Configuration
    dim3 threadsPerBlock(TILE_DIM, TILE_DIM);
    dim3 numBlocks(N / threadsPerBlock.x, N / threadsPerBlock.y);
    srand(100);

    // Memory allocation
    float *matrix_1, *matrix_2, *result;
    matrix_1 = (float*)malloc(N*N*sizeof(float));
    matrix_2 = (float*)malloc(N*N*sizeof(float));
    result = (float*)malloc(N*N*sizeof(float));

    float *d_m1, *d_m2, *d_m3;
    HANDLE_ERROR(cudaMalloc((void**)&d_m1, N*N*sizeof(float)));
    HANDLE_ERROR(cudaMalloc((void**)&d_m2, N*N*sizeof(float)));
    HANDLE_ERROR(cudaMalloc((void**)&d_m3, N*N*sizeof(float)));

    // As per serial, fill these matrices with the right values
    fillIdentity(N, matrix_1, MAT_TL, 1.0f);
    fillRand(N, matrix_1, MAT_TR, 1.0f);
    fillZeros(N, matrix_1, MAT_BL);
    fillIdentity(N, matrix_1, MAT_BR, 1.0f);

    fillIdentity(N, matrix_2, MAT_TL, 1.0f);
    fillRand(N, matrix_2, MAT_TR, 2.0f);
    fillZeros(N, matrix_2, MAT_BL);
    fillIdentity(N, matrix_2, MAT_BR, -1.0f);


    // Copy over the first two matrices, and set up our result matrix
    HANDLE_ERROR(cudaMemcpy(d_m1, matrix_1, N*N*sizeof(float), cudaMemcpyHostToDevice));
    HANDLE_ERROR(cudaMemcpy(d_m2, matrix_2, N*N*sizeof(float), cudaMemcpyHostToDevice));
    HANDLE_ERROR(cudaMemset(d_m3, 0, N*N*sizeof(float)));

    // Do the multiplication
    coalescedMultiply<<<numBlocks, threadsPerBlock>>>(d_m1, d_m2, d_m3, N);

    HANDLE_ERROR(cudaDeviceSynchronize()); // Wait for completion

    // So now d_m3 is our result matrix
    // Re-use matrix_1 for last matrix, to memcpy over to dm_1
    fillIdentity(N, matrix_1, MAT_TL, 1.0f);
    fillRand(N, matrix_1, MAT_TR, -1.0f);
    fillZeros(N, matrix_1, MAT_BL);
    fillIdentity(N, matrix_1, MAT_BR, 1.0f);

    // Multiply d_m3 * d_m1 into d_m2
    // But first set our result matrix to all 0s
    HANDLE_ERROR(cudaMemset(d_m2, 0, N*N*sizeof(float)));
    // Now copy over the new matrix_1
    HANDLE_ERROR(cudaMemcpy(d_m1, matrix_1, N*N*sizeof(float), cudaMemcpyHostToDevice));
    coalescedMultiply<<<numBlocks, threadsPerBlock>>>(d_m3, d_m1, d_m2, N);

    HANDLE_ERROR(cudaThreadSynchronize()); // Wait for completion

    // Copy over d_m2 into matrix_1 for comparison
    HANDLE_ERROR(cudaMemcpy(matrix_1, d_m2, N*N*sizeof(float), cudaMemcpyDeviceToHost));

    // Re-use result for RHS matrix
    fillIdentity(N, result, MAT_TL, 1.0f);
    fillZeros(N, result, MAT_TR);
    fillZeros(N, result, MAT_BL);
    fillIdentity(N, result, MAT_BR, -1.0f);

    printf("LHS:\n");
    printMa(N, matrix_1);

    // Get the error sum
    float error = mat_diff(N, result, matrix_1);

    // Free up memory
    free(matrix_1);
    free(matrix_2);
    free(result);

    HANDLE_ERROR(cudaFree(d_m1));
    HANDLE_ERROR(cudaFree(d_m2));
    HANDLE_ERROR(cudaFree(d_m3));

    // Return the error sum
    return error;
}

int main()
{
    float err = rothVerf_parallel(10);
    printf("Error is %.1f\n", err);
    return 0;
}