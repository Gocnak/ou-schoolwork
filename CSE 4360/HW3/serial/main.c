#include <stdio.h>
#include <sys/time.h>
#include "serial.h"
#include "utils.h"

int main()
{
    double start = get_time();
    float diffSerial = rothVerf_serial(10000);
    printf("Serial diff: %.1f\n in time %.3f ms", diffSerial, (get_time() - start) * 1000.0f);
    return 0;
}