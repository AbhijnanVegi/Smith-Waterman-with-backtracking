#include "helper.h"
#include <sys/time.h>
#include <stdlib.h>

void tick(timer *t)
{
    gettimeofday(t, NULL);
}

double tock(timer *t)
{
    timer now;
    gettimeofday(&now, NULL);
    return ((double)(now.tv_sec - t->tv_sec) * 1000.0f + (double)(now.tv_usec - t->tv_usec) / 1000.0f);
}