#include <stdio.h>
#include <stdint.h>
#include "src/load/load.h"

int main(int, char**){
    printf("Hello, from cstate_monitor!\n");

    uint64_t a = 4307736511339693217;
    if (is_prime(a) == 1){
        printf("%li is prime \n", a);
    } 
    else {
        printf("%li is not prime \n", a);
    }
}
