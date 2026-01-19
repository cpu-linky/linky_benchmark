#include <math.h>
#include <stdio.h>
#include <stdint.h>

int is_prime(uint64_t a){
    // easy and trivial primality test

    uint64_t sqrt_a;
    sqrt_a = (uint64_t)sqrt(a);
    
    for (uint64_t i = 2; i <= sqrt_a; i++){
        if (a % i == 0){
            return 0;
        }
    }

    return 1;
}