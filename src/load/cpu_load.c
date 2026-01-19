#include <math.h>
#include <stdio.h>
#include <stdint.h>


// easy and trivial primality test
int is_prime(uint64_t a){
    uint64_t sqrt_a;
    sqrt_a = (uint64_t)sqrt(a);
    
    for (uint64_t i = 2; i <= sqrt_a; i++){
        if (a % i == 0){
            return 0;
        }
    }

    return 1;
}

/* 
This function return how many prime numbers are inferiors to n.
For n > 10^9 it starts to be a bit long
*/ 
uint64_t prime_counting(uint64_t n){
    uint64_t count = 0;

    for (uint64_t i = 2; i <= n; i ++){
        if (is_prime(i) == 1){
            count ++;
        }
    }

    return count;
}