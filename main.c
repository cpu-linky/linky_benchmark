#include <stdio.h>
#include <stdint.h>
#include "src/load/load.h"

int main(int, char**){
    printf("Hello, from cstate_monitor!\n");

    uint64_t a = 10000000;
    uint64_t count = prime_counting(a);
    
    printf("There are %li prime numbers below %li\n", count, a);
}

