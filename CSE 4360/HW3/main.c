#include <stdio.h>
#include <malloc.h>
#include <memory.h>
#include <stdlib.h>



float* allocate_mem(float*** arr, int n, int m)
{
    *arr = (float**)malloc(n * sizeof(float*));
    float *arr_data = malloc( n * m * sizeof(float));
    for(int i=0; i<n; i++)
        (*arr)[i] = arr_data + i * m ;
    return arr_data; //free point
}

void deallocate_mem(float*** arr, float* arr_data){
    free(arr_data);
    free(*arr);
}

typedef enum
{
    MAT_TL = 0, // Top left
    MAT_TR = 1, // Top right
    MAT_BL = 2, // Bottom left
    MAT_BR = 3 // Bottom right
} MAT_POS;

void findStart(int N, MAT_POS pos, int *i, int *j, int *i_end, int *j_end)
{
    switch (pos)
    {
        case MAT_TL:
            *i = 0;
            *j = 0;
            *i_end = N;
            *j_end = N;
            break;
        case MAT_TR:
            *i = 0;
            *j = N;
            *i_end = N;
            *j_end = 2*N;
            break;
        case MAT_BL:
            *i = N;
            *j = 0;
            *i_end = 2*N;
            *j_end = N;
            break;
        case MAT_BR:
            *i = N;
            *j = N;
            *i_end = 2*N;
            *j_end = 2*N;
            break;
    }
}

void fillIdentity(int N, float **matrix, MAT_POS pos)
{
    // Assuming it's NxN
    //int posi = (N*N*pos);

    int i_start, j_start, i_end, j_end;
    findStart(N, pos, &i_start, &j_start, &i_end, &j_end);
    for (int i = i_start; i < i_end; i++)
    {
        for (int j = j_start; j < j_end; j++)
        {
            matrix[i][j] = (i == j) ? 1.0f : 0.0f;
        }
    }
}

void fillZeros(int N, float **matrix, MAT_POS pos)
{
    int i_start, j_start, i_end, j_end;
    findStart(N, pos, &i_start, &j_start, &i_end, &j_end);
    for (int i = i_start; i < i_end; i++)
    {
        for (int j = j_start; j < j_end; j++)
        {
            matrix[i][j] = 0.0f;
        }
    }
}

void fillRand(int N, float **matrix, MAT_POS pos)
{
    srand(100);
    int i_start, j_start, i_end, j_end;
    findStart(N, pos, &i_start, &j_start, &i_end, &j_end);
    for (int i = i_start; i < i_end; i++)
    {
        for (int j = j_start; j < j_end; j++)
        {
            matrix[i][j] = rand() / (float)RAND_MAX;
        }
    }
}

void printMatrix(int N, float **matrix)
{
    for (int i = 0; i < 2*N; i++)
    {
        for (int j = 0; j < 2*N; j++)
        {
            printf("%.1f\t", matrix[i][j]);
        }
        printf("\n");
    }
}

float rothVerf(int N)
{

    float **matrix;
    float *free_point = allocate_mem(&matrix, N*2, N*2);
    //float *result = (float*)calloc(N*N*4, sizeof(float));

    fillIdentity(N, matrix, MAT_TL);
    fillRand(N, matrix, MAT_TR);
    fillZeros(N, matrix, MAT_BL);
    fillIdentity(N, matrix, MAT_BR);

    printMatrix(N, matrix);

    deallocate_mem(&matrix, free_point);
    //free(result);
}


int main()
{
    rothVerf(10);
    return 0;
}