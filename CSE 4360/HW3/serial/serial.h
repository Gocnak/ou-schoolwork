//
// Created by nick on 4/3/18.
//
#pragma once

typedef enum
{
    MAT_TL = 0, // Top left
    MAT_TR = 1, // Top right
    MAT_BL = 2, // Bottom left
    MAT_BR = 3 // Bottom right
} MAT_POS;

inline void findStart(int N, MAT_POS pos, int *i, int *j, int *i_end, int *j_end)
{
    *i = (pos < MAT_BL) ? 0 : N;
    *j = (pos % 2 == 1) ? N : 0;
    *i_end = (pos < MAT_BL) ? N : 2*N;
    *j_end = (pos % 2 == 1) ? 2*N : N;
}

float rothVerf_serial(int N);