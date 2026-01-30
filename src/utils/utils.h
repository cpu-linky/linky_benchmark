#ifndef UTILS_H
#define UTILS_H

int run_with_affinity(int cpu, void (*func)(void*), void* args);
int set_affinity(int cpu);

#endif // UTILS_H