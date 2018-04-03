//
// Created by nick on 4/3/18.
//

#include <sys/time.h>
#include <stdio.h>
#include "utils.h"

// gets the current time in seconds with microsecond precision
double get_time()
{
    struct timeval t;
    struct timezone tzp;
    gettimeofday(&t, &tzp);
    return t.tv_sec + t.tv_usec * 1e-6;
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

