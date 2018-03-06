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
#define KEY_COUNT (256*256)//(1024*1024)

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

    int maxRange = args->offset + (KEY_COUNT / NUM_THREADS);
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

int main(char *argv, int argc)
{
    //int index;
    //int error;
    map_t mymap;
    //char key_string[KEY_MAX_LENGTH];
    //data_struct_t *value;

    mymap = hashmap_new(KEY_COUNT);


    double startTime = get_time();

    pthread_t threads[NUM_THREADS];
    for (int i = 0; i < NUM_THREADS; i++) {
        thread_args *args = (thread_args *) malloc(sizeof(thread_args));
        args->map = mymap;
        args->offset = i;
        pthread_create(&threads[i], NULL, HashThread, (void *) args);
    }

    for (int i = 0; i < NUM_THREADS; i++)
        pthread_join(threads[i], NULL);


    double time = get_time() - startTime;
    printf("Total duration %.3f seconds (%.3f msec)\n", time, time * 1000.0);


    /*pthread_barrier_init(&barrier, NULL, NUM_THREADS);
    // -- PUT --
    *//* First, populate the hash map with ascending values *//*
    for (index = 0; index < KEY_COUNT; index += 1) {
        *//* Store the key string along side the numerical value so we can free it later *//*
        value = malloc(sizeof(data_struct_t));
        snprintf(value->key_string, KEY_MAX_LENGTH, "%s%d", KEY_PREFIX, index);
        value->number = index;

        error = hashmap_put(mymap, value->key_string, value);
        if (error != MAP_OK)
            printf("NOT OKAY WITH KEY %s\n", value->key_string);
        assert(error == MAP_OK);
    }

    // -- GET --
    *//* Now, check all of the expected values are there *//*
    for (index = 0; index < KEY_COUNT; index += 1) {
        snprintf(key_string, KEY_MAX_LENGTH, "%s%d", KEY_PREFIX, index);

        error = hashmap_get(mymap, key_string, (void **) (&value));

        *//* Make sure the value was both found and the correct number *//*
        assert(error == MAP_OK);
        assert(value->number == index);
    }


    *//* Make sure that a value that wasn't in the map can't be found *//*
    snprintf(key_string, KEY_MAX_LENGTH, "%s%d", KEY_PREFIX, KEY_COUNT);

    error = hashmap_get(mymap, key_string, (void **) (&value));

    *//* Make sure the value was not found *//*
    assert(error == MAP_MISSING);

    *//* Free all of the values we allocated and remove them from the map *//*
    for (index = 0; index < KEY_COUNT; index += 1) {
        snprintf(key_string, KEY_MAX_LENGTH, "%s%d", KEY_PREFIX, index);

        error = hashmap_get(mymap, key_string, (void **) (&value));
        assert(error == MAP_OK);

        error = hashmap_remove(mymap, key_string);
        assert(error == MAP_OK);

        free(value);
    }*/

    /* Now, destroy the map */
    hashmap_free(mymap);

    return 1;
}