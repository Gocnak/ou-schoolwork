/* a simple openMP program */

#include <stdio.h>

#include <omp.h>

int main(int argc, char *argv[]){

    int num_threads = 999999;

    // omp_set_num_threads(4);
    // or use num_threads(4) as part of the pragma below
    #pragma omp parallel
    {
        int thread_id = omp_get_thread_num();

        #pragma omp master
        {
            num_threads = omp_get_num_threads();
        }

        #pragma omp barrier

        printf("Hello from thread %d nthread %d\n", thread_id, num_threads);
        
    } // End of Parallel region
    return 0;
}

