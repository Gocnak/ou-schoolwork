//
// Created by nick on 4/3/18.
//

#include <sys/time.h>
#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include "utils.h"



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



