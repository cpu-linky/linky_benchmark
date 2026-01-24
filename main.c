#include <stdio.h>
#include <stdint.h>
#include "src/load/load.h"

int main(int, char**){
    int n = 100000000;
    printf("Counting how many prime below %d\n", n);
    prime_counting(n);
}