#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include "src/env/env.h"

int main() {
    // Load env and build commands
    load_env_file("config.env");
    
    char *command_cpu[] = {"turbostat", "--quiet", "--interval", "1", "bin/cpu_load", "10000000", NULL};
    char *command_mem[] = {"turbostat", "--quiet", "--interval", "1", "bin/memory_load", "10000000", NULL};
    char *command_io[] = {"turbostat", "--quiet", "--interval", "1", "bin/io_load", "300", NULL};

    char *cpu_n_pi = getenv("CPU_N_PI");
    char *n_cpu = getenv("N_CPU");

    char *mem_n_jumps = getenv("MEMORY_N_JUMPS");
    char *n_memory = getenv("N_MEMORY");

    char *io_n_dumps = getenv("IO_N_DUMPS");
    char *n_io = getenv("N_IO");

    command_cpu[5] = cpu_n_pi;
    command_mem[5] = mem_n_jumps;
    command_io[5] = io_n_dumps;

    // Fork 1 : CPU Load
    pid_t pid = fork();
    if (pid == 0) {
        execvp(command_cpu[0], command_cpu);
        perror("[ERROR] execvp failed for CPU load");
        return 1;
    } else if (pid > 0) {
        int status;
        waitpid(pid, &status, 0);
        printf("[SUCCESS] CPU load test done! (Exit code : %d)\n", WEXITSTATUS(status));
    } else {
        perror("[ERROR] Fail to fork CPU load");
    }

    // Fork 2 : memory load
    pid = fork();
    if (pid == 0) {
        execvp(command_mem[0], command_mem);
        perror("[ERROR] execvp failed for memory load");
        return 1;
    } else if (pid > 0) {
        int status;
        waitpid(pid, &status, 0);
        printf("[SUCCESS] Memory load test done! (Exit code : %d)\n", WEXITSTATUS(status));
    } else {
        perror("[ERROR] Fail to fork Memory load");
    }

    // Fork 3 : io load
    pid = fork();
    if (pid == 0) {
        execvp(command_io[0], command_io);
        perror("[ERROR] execvp failed for io load");
        return 1;
    } else if (pid > 0) {
        int status;
        waitpid(pid, &status, 0);
        printf("[SUCCESS] IO load test done! (Exit code : %d)\n", status);
    } else {
        perror("[ERROR] Fail to fork io load");
    }

    return 0;
}