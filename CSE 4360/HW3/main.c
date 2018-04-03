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

void fillIdentity(int N, float **matrix, MAT_POS pos, float scalar)
{
    // Assuming it's NxN
    //int posi = (N*N*pos);

    int i_start, j_start, i_end, j_end;
    findStart(N, pos, &i_start, &j_start, &i_end, &j_end);
    for (int i = i_start; i < i_end; i++)
    {
        for (int j = j_start; j < j_end; j++)
        {
            matrix[i][j] = (i == j) ? (scalar) : 0.0f;
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

void fillRand(int N, float **matrix, MAT_POS pos, float scalar)
{
    int i_start, j_start, i_end, j_end;
    findStart(N, pos, &i_start, &j_start, &i_end, &j_end);
    for (int i = i_start; i < i_end; i++)
    {
        for (int j = j_start; j < j_end; j++)
        {
            matrix[i][j] = scalar * (rand() / (float)RAND_MAX);
        }
    }
}

void printMatrix(int N, float **matrix)
{
    for (int i = 0; i < 2*N; i++)
    {
        for (int j = 0; j < 2*N; j++)
        {
            printf("%.1f ", matrix[i][j]);
        }
        printf("\n");
    }
}

//Assuming NxN matricies
void matMul(int N, float **matrix1, float **matrix2, float **result)
{
    int sqr = N*N;
    memset(*result, 0, sqr * sizeof(float));

    for (int ijk = 0; ijk < sqr; ijk++)
    {
        int i = ijk / sqr;
        int j = (ijk / N) % N;
        int k = ijk % N;
        result[i][j] += matrix1[i][k] * matrix2[k][j];
    }
}

float rothVerf(int N)
{
    float **matrix_1, **matrix_2, **result;
    float *free_point_1 = allocate_mem(&matrix_1, N*2, N*2);
    float *free_point_2 = allocate_mem(&matrix_2, N*2, N*2);
    float *free_point_3 = allocate_mem(&result, N*2, N*2);

    srand(100);

    fillIdentity(N, matrix_1, MAT_TL, 1.0f);
    fillRand(N, matrix_1, MAT_TR, 1.0f);
    fillZeros(N, matrix_1, MAT_BL);
    fillIdentity(N, matrix_1, MAT_BR, 1.0f);

    fillIdentity(N, matrix_2, MAT_TL, 1.0f);
    fillRand(N, matrix_2, MAT_TR, 2.0f);
    fillZeros(N, matrix_2, MAT_BL);
    fillIdentity(N, matrix_2, MAT_BR, -1.0f);

    // Multiply these two
    matMul(2*N, matrix_1, matrix_2, result);

    // Re-use matrix_1 for last matrix
    fillIdentity(N, matrix_1, MAT_TL, 1.0f);
    fillRand(N, matrix_1, MAT_TR, -1.0f);
    fillZeros(N, matrix_1, MAT_BL);
    fillIdentity(N, matrix_1, MAT_BR, 1.0f);

    // Multiply result * matrix_1 into matrix_2
    matMul(2*N, result, matrix_1, matrix_2);

    // Re-use result for RHS matrix
    fillIdentity(N, result, MAT_TL, 1.0f);
    fillZeros(N, result, MAT_TR);
    fillZeros(N, result, MAT_BL);
    fillIdentity(N, result, MAT_BR, -1.0f);

    // Compare matrix_2 and result
    /*printf("LHS:\n");
    printMatrix(N, matrix_2);
    printf("RHS:\n");
    printMatrix(N, result);*/

    deallocate_mem(&matrix_1, free_point_1);
    deallocate_mem(&matrix_2, free_point_2);
    deallocate_mem(&result, free_point_3);
}


int main()
{
    rothVerf(10000);
    return 0;
}