#define _GNU_SOURCE
#include <sched.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

// Set the CPU affinity of the current process to the given CPU
int set_affinity(int cpu) {

    cpu_set_t cpuset;
    CPU_ZERO(&cpuset);          // empty the cpu list
    CPU_SET(cpu, &cpuset);      // add only the target cpu 
    pid_t pid = getpid();       

    // try to set the affinity of the current task to the target cpu
    if (sched_setaffinity(pid, sizeof(cpu_set_t), &cpuset) != 0){
        perror("sched_setaffinity failed");
        return -1;
    }

    return 0;
}