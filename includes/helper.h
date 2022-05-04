#ifndef HELPER_H
#define HELPER_H

#include <sys/time.h>
typedef struct timeval timer;

void tick(timer* t);
double tock(timer* t);

#endif