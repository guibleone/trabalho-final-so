#include <stdio.h>
#include <time.h>

#include "mainUtils.h"

void handleTime(const struct timespec *start, const struct timespec *end)
{
    double totalTime = (end->tv_sec - start->tv_sec) + (end->tv_nsec - start->tv_nsec) / 1e8;
    printf("Time stamp of reading all files: %f\n", totalTime);
}
