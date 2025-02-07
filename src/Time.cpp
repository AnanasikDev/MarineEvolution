#include "Time.h"

time_t start = 0;

void initTime(){
    start = time(0);
}

float getTime(){
    return difftime( time(0), start) * simSpeed;
}

void resetTime(){
    initTime();
}