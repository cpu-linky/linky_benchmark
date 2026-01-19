#include <math.h>
#include <stdio.h>

int is_prime(int a){
    // easy and trivial primality test

    double sqrt_a;
    sqrt_a = sqrt(a);
    
    for (int i = 2; i < sqrt_a; i++){
        if (a % i == 0){
            return 0;
        }
    }

    return 1;
}