//
// Created by nick on 4/3/18.
//
#include "cuda.h"
#include "parallel.h"
#include <stdio.h>

#define TILE_DIM 16

__global__ void coalescedMultiply(float *a, float *b, float *c, int N)
{
    __shared__ float aTile[TILE_DIM][TILE_DIM], bTile[TILE_DIM][TILE_DIM];

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
    c[row*N+col] = sum;
}


float rothVerf_parallel(int N)
{
    return 0.0f;
}

int main()
{
    printf("Hello!\n");
    return 0;
}