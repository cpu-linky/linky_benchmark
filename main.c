#include <stdio.h>
#include "src/load/load.h"

int main(int, char**){
    printf("Hello, from cstate_monitor!\n");

    int a = 81992911;
    if (is_prime(a) == 1){
        printf("%d is prime \n", a);
    } 
    else {
        printf("%d is not prime \n", a);
    }
}
