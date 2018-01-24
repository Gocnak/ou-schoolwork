//
// Created by nick on 1/17/18.
//
#include <unistd.h>
#include <stdlib.h>
#include <omp.h>
#include <stdio.h>


int main() {


    int IS = 0;
#pragma omp parallel for reduction(+:IS)
    for (int i = 1; i <= 10; i++) {
        IS = IS + i;
    }

    printf("%d", IS);

}