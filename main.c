#include <stdio.h>
#include <stdint.h>
#include "src/load/load.h"

int main(int, char**){
    printf("Hello from cstate monitor\n");

    int jumps = 1000000;
    printf("Performing a pointer chase with %d jumps\n", jumps);

    pointer_chase(jumps);
}