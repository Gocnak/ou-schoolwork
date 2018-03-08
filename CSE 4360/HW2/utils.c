#include <stdint.h>
#include <sys/time.h>

#include "utils.h"

int
bitmask_at(uint8_t * mask, unsigned i) {
    return (mask[i / 8u] >> (i % 8u)) & 1u;
}

void
bitmask_set(uint8_t * mask, unsigned i) {
    mask[i / 8u] |= 1u << (i % 8u);
}

void
bitmask_unset(uint8_t * mask, unsigned i) {
    mask[i / 8u] &= ~(1u << (i % 8u));
}

// gets the current time in seconds with microsecond precision
double get_time()
{
    struct timeval t;
    struct timezone tzp;
    gettimeofday(&t, &tzp);
    return t.tv_sec + t.tv_usec * 1e-6;
}

