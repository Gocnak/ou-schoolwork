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
    int isTop = (pos < MAT_BL);
    int isRight = (pos % 2 == 1);

    *i = (isTop) ? 0 : N/2;
    *j = (isRight) ? N/2 : 0;
    *i_end = (isTop) ? N/2 : N;
    *j_end = (isRight) ? N : N/2;
}