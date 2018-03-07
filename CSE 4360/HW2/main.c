/*
 * A unit test and example of how to use the simple C hashmap
 */

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "pthread.h"
#include <sys/time.h>
#include "hashmap.h"

#define KEY_MAX_LENGTH (256)
#define KEY_PREFIX ("somekey")
#define KEY_COUNT (1024*1024)

#define NUM_THREADS 6

typedef struct data_struct_s
{
    char key_string[KEY_MAX_LENGTH];
    int number;
} data_struct_t;

typedef struct
{
    map_t map;
    int offset;
} thread_args;

// gets the current time in seconds with microsecond precision
double get_time()
{
    struct timeval t;
    struct timezone tzp;
    gettimeofday(&t, &tzp);
    return t.tv_sec + t.tv_usec * 1e-6;
}

void *HashThread(void *params)
{
    thread_args *args = (thread_args *) params;
    char key_string[KEY_MAX_LENGTH];
    int error;
    data_struct_t *value;

    int maxRange = (KEY_COUNT / NUM_THREADS);
    //printf("Max range for thread %d : %d\n", args->offset, maxRange);
    for (int i = args->offset; i < maxRange; i++) {
        value = (data_struct_t *) malloc(sizeof(data_struct_t));
        snprintf(value->key_string, KEY_MAX_LENGTH, "%s%d", KEY_PREFIX, i);
        value->number = i;

        error = hashmap_put(args->map, value->key_string, value);
        if (error != MAP_OK)
            printf("NOT OKAY WITH KEY %s\n", value->key_string);
        assert(error == MAP_OK);
    }

    for (int i = args->offset; i < maxRange; i++) {
        snprintf(key_string, KEY_MAX_LENGTH, "%s%d", KEY_PREFIX, i);

        error = hashmap_get(args->map, key_string, (void **) (&value));
        assert(error == MAP_OK);

        error = hashmap_remove(args->map, key_string);
        assert(error == MAP_OK);

        free(value);
    }
}

double run_test(unsigned long long K)
{
    map_t mymap = hashmap_new(KEY_COUNT, K);
    
    double startTime = get_time();
    
    pthread_t threads[NUM_THREADS];
    for (int i = 0; i < NUM_THREADS; i++) {
        thread_args *args = (thread_args *) malloc(sizeof(thread_args));
        args->map = mymap;
        args->offset = i * (KEY_COUNT / NUM_THREADS);
        pthread_create(&threads[i], NULL, HashThread, (void *) args);
    }
    
    for (int i = 0; i < NUM_THREADS; i++)
        pthread_join(threads[i], NULL);
    
    double time = get_time() - startTime;
    //printf("Total duration %.3f seconds (%.3f msec)\n", time, time * 1000.0);
    
    /* Now, destroy the map */
    hashmap_free(mymap);
    
    return time;
}

#define TEST_ITER 1 // how many times to run the test to average against
#define MAX_K 1000 // the maximum number of K locks

int main(char *argv, int argc)
{
    double results[MAX_K];
    for (int i = 0; i < MAX_K; i++)
    {
        double sum = 0.0;
        for (int j = 0; j < TEST_ITER; j++)
        {
            sum += run_test((unsigned long long int) i + 1);
        }
        
        results[i] = sum / TEST_ITER;
        printf("Result for %d : %.3f msec\n", i, results[i]);
        
    }

    return 1;
}