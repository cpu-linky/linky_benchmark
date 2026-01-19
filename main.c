#include <stdio.h>
#include <stdint.h>
#include "src/load/load.h"

int main(int, char**){
    printf("Hello, from cstate_monitor!\n");

    dump_io();
}