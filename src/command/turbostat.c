#include <stdlib.h>
#include <string.h>
#include <stdio.h>

// Run the given command with turbostat as profiler 
int run_with_turbostat(char* cmd) {
    char base_cmd[] = "turbostat --quiet";
    char full_cmd[512];
    char end_cmd[] = " > out.txt";
 
    snprintf(full_cmd, sizeof(full_cmd), "%s%s%s", base_cmd, cmd, end_cmd);
    int ret = system(full_cmd);
    return ret;
}