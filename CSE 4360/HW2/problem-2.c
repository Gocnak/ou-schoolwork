#include <stdio.h>
#include <stdint.h>
#include <limits.h>
#include <stdlib.h>
#include <time.h>

#include "pthread.h"
#include "set.h"
#include "map.h"
#include "priority_queue.h"
#include "utils.h"

/*
 * Initial 15-puzzle solver code from https://github.com/NolanRus/15-puzzle-solver
 * by NolanRus
 *
 * Threaded modifications by me
 */

static uint64_t make_field(a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p)
        uint64_t a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p;
{
    return ((a & 0xf) << (0 * 4)) | ((b & 0xf) << (1 * 4)) |
           ((c & 0xf) << (2 * 4)) | ((d & 0xf) << (3 * 4)) |
           ((e & 0xf) << (4 * 4)) | ((f & 0xf) << (5 * 4)) |
           ((g & 0xf) << (6 * 4)) | ((h & 0xf) << (7 * 4)) |
           ((i & 0xf) << (8 * 4)) | ((j & 0xf) << (9 * 4)) |
           ((k & 0xf) << (10 * 4)) | ((l & 0xf) << (11 * 4)) |
           ((m & 0xf) << (12 * 4)) | ((n & 0xf) << (13 * 4)) |
           ((o & 0xf) << (14 * 4)) | ((p & 0xf) << (15 * 4));
}

static unsigned field_at(uint64_t field, unsigned row, unsigned col)
{
    return (field >> ((row * 4 + col) * 4)) & 0xf;
}

static void print_field(uint64_t field)
{
    for (unsigned i = 0; i < 4; ++i)
    {
        for (unsigned j = 0; j < 4; ++j)
        {
            unsigned x = field_at(field, i, j);
            if (x)
            {
                printf("%2d ", x);
            } else
            {
                printf("   ");
            }
        }
        putchar('\n');
    }
}

static void reconstruct_path(struct Map *came_from, uint64_t field)
{
    unsigned path_length = 0;
    while (field)
    {
        print_field(field);
        putchar('\n');
        field = map_at(came_from, field);
        ++path_length;
    }
    printf("length: %d\n", path_length);
}

#define ABSDIFF(a, b) ((a) < (b) ? (b) - (a) : (a) - (b))

static unsigned heuristic_cost_estimate(uint64_t field)
{
    unsigned h = 0;
    for (unsigned i = 0; i < 4; ++i)
    {
        for (unsigned j = 0; j < 4; ++j)
        {
            unsigned x = field_at(field, i, j);
            unsigned ii = ((x + 15) % 16) / 4;
            unsigned jj = ((x + 15) % 16) % 4;
            h += ABSDIFF(ii, i) + ABSDIFF(jj, j);
        }
    }
    return h;
}

static uint64_t field_set(uint64_t field, uint64_t row, uint64_t col, uint64_t x)
{
    return (field & ~(0xfull << ((row * 4 + col) * 4)))
           | (x << ((row * 4 + col) * 4));
}

static uint64_t field_swap(uint64_t field, unsigned y0, unsigned x0,
           unsigned y1, unsigned x1)
{
    unsigned x0y0 = field_at(field, y0, x0);
    unsigned x1y1 = field_at(field, y1, x1);
    field = field_set(field, y0, x0, x1y1);
    field = field_set(field, y1, x1, x0y0);
    return field;
}

static void find_zero(uint64_t field, unsigned *zy, unsigned *zx)
{
    for (unsigned i = 0; i < 4; ++i)
    {
        for (unsigned j = 0; j < 4; ++j)
        {
            if (field_at(field, i, j)) continue;
            *zy = i;
            *zx = j;
            return;
        }
    }
}

static void get_neighbors(uint64_t current, uint64_t (*neighbors)[4], unsigned *n)
{
    unsigned zy, zx;
    find_zero(current, &zy, &zx);
    *n = 0;
    if (zy)
    {
        (*neighbors)[(*n)++] = field_swap(current, zy, zx, zy - 1, zx);
    }
    if (zx != 3)
    {
        (*neighbors)[(*n)++] = field_swap(current, zy, zx, zy, zx + 1);
    }
    if (zy != 3)
    {
        (*neighbors)[(*n)++] = field_swap(current, zy, zx, zy + 1, zx);
    }
    if (zx)
    {
        (*neighbors)[(*n)++] = field_swap(current, zy, zx, zy, zx - 1);
    }
}

static uint64_t goal;

typedef struct
{
    struct Set *closed_set;
    struct PriorityQueue *open_queue;
    struct Map *came_from;
    struct Map *g_score;
    struct Map *f_score;
} thread_args;

void *SolverWorker(void *params)
{
    thread_args *args = (thread_args*) params;
    
    uint64_t current = queue_extract_min(args->open_queue);
    
    if (current == goal)
    {
        return (void*)current;
    }
    
    set_add(args->closed_set, current);
    uint64_t neighbors[4];
    unsigned n;
    get_neighbors(current, &neighbors, &n);
    for (unsigned i = 0; i < n; ++i)
    {
        uint64_t neighbor = neighbors[i];
        /* Ignore the neighbor which is already evaluated. */
        if (set_has(args->closed_set, neighbor))
            continue;
        
        if (!queue_has(args->open_queue, neighbor))
        {
            /* Discover a new node. */
            queue_add(args->open_queue, UINT_MAX, neighbor);
        }
        /* The distance from start to a neighbor. */
        unsigned tentative_gScore = map_at(args->g_score, current) + 1;
        
        /* If this is not a better path. */
        if (!map_has(args->g_score, neighbor))
        {
            map_set(args->g_score, neighbor, UINT_MAX);
        }
        if (tentative_gScore >= map_at(args->g_score, neighbor))
            continue;
        
        /* This path is the best until now. Record it! */
        map_set(args->came_from, neighbor, current);
        map_set(args->g_score, neighbor, tentative_gScore);
        unsigned t = tentative_gScore + heuristic_cost_estimate(neighbor);
        map_set(args->f_score, neighbor, t);
        queue_reduce_key(args->open_queue, t, neighbor);
    }
    
    return NULL;
}

#define USE_PTHREAD
#define NUM_THREADS 12 // Maximum number of threads
#define MIN(val1, val2) ((val1) < (val2) ? (val1) : (val2))

#if PROBLEM_2
int main()
{
    uint64_t start = make_field(2, 7, 0, 11, 1, 8, 4, 3, 5, 6, 14, 12, 10, 9, 15, 13);
    
    /*srand(time(NULL));
    uint64_t start = make_field(1, 2, 3, 4,
                                5, 6, 7, 8,
                                9, 10, 11, 12,
                                13, 14, 15, 0);
    for (int i = 0; i < 100; ++i)
    {
        uint64_t neighbors[4];
        unsigned n;
        get_neighbors(start, &neighbors, &n);
        start = neighbors[rand() % n];
    }*/
    
    print_field(start);
    puts("-=========-");
    goal = make_field(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 0);
    /* The set of nodes already evaluated */
    static struct Set closed_set;
    set_init(&closed_set);
    /* The set of currently discovered nodes that are not evaluated yet.
       Initially, only the start node is known. */
    static struct PriorityQueue open_queue;
    queue_init(&open_queue);
    queue_add(&open_queue, 0, start);
    /* For each node, which node it can most efficiently be reached from.
       If a node can be reached from many nodes, cameFrom will eventually
       contain the most efficient previous step. */
    static struct Map came_from;
    map_init(&came_from);
    map_set(&came_from, start, 0);
    /* For each node, the cost of getting from the start node to that node. */
    static struct Map g_score;
    map_init(&g_score);
    /* The cost of going from start to start is zero. */
    map_set(&g_score, start, 0);
    /* For each node, the total cost of getting from the start node to the goal
       by passing by that node. That value is partly known, partly
       heuristic. */
    static struct Map f_score;
    map_init(&f_score);
    /* For the first node, that value is completely heuristic. */
    map_set(&f_score, start, heuristic_cost_estimate(start));
    
#ifdef USE_PTHREAD
    pthread_t *threads = (pthread_t *) calloc(NUM_THREADS, sizeof(pthread_t));
#endif
    
    double startTime = get_time();
    
    while (!queue_is_empty(&open_queue))
    {
#ifdef USE_PTHREAD
        int size = queue_size(&open_queue);
        int numthreads = NUM_THREADS;//MIN(size, NUM_THREADS);
    
        thread_args args;
        args.closed_set = &closed_set;
        args.open_queue = &open_queue;
        args.f_score = &f_score;
        args.g_score = &g_score;
        args.came_from = &came_from;
        
        for (int i = 0; i < numthreads; i++)
        {
            pthread_create(&threads[i], NULL, SolverWorker, (void*) &args);
        }
        
        int done = 0;
        
        for (int i = 0; i < numthreads; i++)
        {
            void* output;
            pthread_join(threads[i], &output);
            uint64_t solution = (uint64_t)output;
            if (solution)
            {
                double endTimeMS = (get_time() - startTime) * 1000.0f;
                reconstruct_path(&came_from, solution);
                printf("Total duration: %.3f msec\n", endTimeMS);
                done = 1;
                break;
            }
        }
        
        if (done)
        {
            free(threads);
            return 0;
        }
        
#else
        uint64_t current = queue_extract_min(&open_queue);
        
        if (current == goal)
        {
            reconstruct_path(&came_from, current);
            printf("Total duration: %.3f msec\n", (get_time() - startTime) * 1000.0f);
            return 0;
        }
        
        set_add(&closed_set, current);
        uint64_t neighbors[4];
        unsigned n;
        get_neighbors(current, &neighbors, &n);
        for (unsigned i = 0; i < n; ++i)
        {
            uint64_t neighbor = neighbors[i];
            /* Ignore the neighbor which is already evaluated. */
            if (set_has(&closed_set, neighbor))
                continue;
        
            if (!queue_has(&open_queue, neighbor))
            {
                /* Discover a new node. */
                queue_add(&open_queue, UINT_MAX, neighbor);
            }
            /* The distance from start to a neighbor. */
            unsigned tentative_gScore = map_at(&g_score, current) + 1;
        
            /* If this is not a better path. */
            if (!map_has(&g_score, neighbor))
            {
                map_set(&g_score, neighbor, UINT_MAX);
            }
            if (tentative_gScore >= map_at(&g_score, neighbor))
                continue;
        
            /* This path is the best until now. Record it! */
            map_set(&came_from, neighbor, current);
            map_set(&g_score, neighbor, tentative_gScore);
            unsigned t = tentative_gScore + heuristic_cost_estimate(neighbor);
            map_set(&f_score, neighbor, t);
            queue_reduce_key(&open_queue, t, neighbor);
        }
#endif
    }
    printf("No solutions found.\n");
}
#endif
