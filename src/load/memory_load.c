#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>
#include <unistd.h>

// Size of the main array : 256MB, enough to be superiour to any L3 cache
// sizeof(size_t) = 8 bytes
// 32 * 1024 * 1024 éléments * 8 octets = 256 MB
#define NUM_ELEMENTS (32 * 1024 * 1024)

// Perform a pointer chase on an array in RAM
int pointer_chase(int jumps) {

    // create a big a** array
    size_t *memory_array = malloc(NUM_ELEMENTS * sizeof(size_t));
    if (memory_array == NULL) {
        perror("Fail to allocate memory array");
        return 1;
    }

    // temp array to store indexes
    size_t *index_array = malloc(NUM_ELEMENTS * sizeof(size_t));
    if (index_array == NULL) {
        perror("Fail to allocate index array");
        free(memory_array);
        return 1;
    }
    for (size_t i = 0; i < NUM_ELEMENTS; i++) {
        index_array[i] = i;
    }

    // shuffle main array using Fisher-Yates shuffle
    srand(time(NULL));
    for (size_t i = NUM_ELEMENTS - 1; i > 0; i --) {
        size_t j = rand() % (i + 1);
        size_t temp = index_array[j];
        index_array[j] = index_array[i];
        index_array[i] = temp;
    }

    /*Create the main array
    Where each element points to the next one*/
    for (size_t i = 0; i < NUM_ELEMENTS - 1; i ++){
        memory_array[index_array[i]] = index_array[i + 1];
    } 
    // the last element points to the first
    memory_array[index_array[NUM_ELEMENTS - 1]] = index_array[0];

    free(index_array);

    // actual chasing pointer loop:
    size_t current_index = 0;
    for (size_t index = 0; index < jumps; index ++) {
        current_index = memory_array[current_index];
    }

    // to prevent dead code
    if (current_index == 69){
        printf("Im still standing!!!\n");
    } 

    free(memory_array);
    return 0;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <jumps>\n", argv[0]);
        return 1;
    }

    int jumps = atoi(argv[1]);
    if (pointer_chase(jumps) != 0) {
        return 1;
    }

    printf("#| Completed %d pointer jumps in memory.\n", jumps);
    return 0;
}