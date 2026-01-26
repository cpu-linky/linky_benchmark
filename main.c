#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include "src/env/env.h"

int main() {
    // Load env and build commands
    load_env_file("config.env");
    
    char *command_cpu[] = {"turbostat", "--quiet", "--interval", "1", "bin/cpu_load", "10000000", NULL};
    char *command_mem[] = {"turbostat", "--quiet", "--interval", "1", "bin/memory_load", "10000000", NULL};
    char *command_io[] = {"turbostat", "--quiet", "--interval", "1", "bin/io_load", "300", NULL};

    char *cpu_n_pi = getenv("CPU_N_PI");
    int n_cpu = atoi(getenv("N_CPU"));
    char *cpu_log_path = getenv("CPU_LOG_PATH");

    char *mem_n_jumps = getenv("MEMORY_N_JUMPS");
    int n_memory = atoi(getenv("N_MEMORY"));
    char *memory_log_path = getenv("MEMORY_LOG_PATH");

    char *io_n_dumps = getenv("IO_N_DUMPS");
    int n_io = atoi(getenv("N_IO"));
    char *io_log_path = getenv("IO_LOG_PATH");


    command_cpu[5] = cpu_n_pi;
    command_mem[5] = mem_n_jumps;
    command_io[5] = io_n_dumps;

    //TODO: add cpu affinity to record only the targeted cpu

    pid_t pid;

    // Fork 1 : CPU Load
    printf("[INFO] CPU test begins : %d cycles\n", n_cpu);
    for (int i = 0; i < n_cpu; i++) {
        pid = fork();
        if (pid == 0) {
            // create a log file to record everything
            char log_filename[64];
            snprintf(log_filename, sizeof(log_filename), "%s", cpu_log_path);

            int fd = open(log_filename, O_WRONLY | O_CREAT | O_APPEND, 0644);

            if (fd == -1){
                perror("[ERROR] Failed to open log file");
                return -1;
            }

            dup2(fd, STDOUT_FILENO);
            dup2(fd, STDERR_FILENO);
            close(fd);

            execvp(command_cpu[0], command_cpu);
            perror("[ERROR] execvp failed for CPU load");
            return 1;
        } else if (pid > 0) {
            int status;
            waitpid(pid, &status, 0);
            printf("[INFO] CPU load cycle no %d done! (Exit code : %d)\n", i, WEXITSTATUS(status));
        } else {
            perror("[ERROR] Fail to fork CPU load");
        }
    }
    printf("[SUCCESS] CPU : all %d cycles are done\n", n_cpu);

    // Fork 2 : memory load
    printf("[INFO] Memory test begins : %d cycles\n", n_memory);   
    for (int i = 0; i < n_memory; i ++){
        pid = fork();
        if (pid == 0) {
            // create a log file to record everything
            char log_filename[64];
            snprintf(log_filename, sizeof(log_filename), "%s", memory_log_path);

            int fd = open(log_filename, O_WRONLY | O_CREAT | O_APPEND, 0644);

            if (fd == -1){
                perror("[ERROR] Failed to open log file");
                return -1;
            }

            dup2(fd, STDOUT_FILENO);
            dup2(fd, STDERR_FILENO);
            close(fd);

            execvp(command_mem[0], command_mem);
            perror("[ERROR] execvp failed for memory load");
            return 1;
        } else if (pid > 0) {
            int status;
            waitpid(pid, &status, 0);
            printf("[INFO] Memory load cycle no %d done! (Exit code : %d)\n", i, WEXITSTATUS(status));
        } else {
            perror("[ERROR] Fail to fork Memory load");
        }
    }
    printf("[SUCCESS] Memory : all %d cycles are done\n", n_memory);

    // Fork 3 : io load
    printf("[INFO] I/O test begins : %d cycles\n", n_io);  
    for (int i = 0; i < n_io; i++) {
        pid = fork();
        if (pid == 0) {
            // create a log file to record everything
            char log_filename[64];
            snprintf(log_filename, sizeof(log_filename), "%s", io_log_path);

            int fd = open(log_filename, O_WRONLY | O_CREAT | O_APPEND, 0644);

            if (fd == -1){
                perror("[ERROR] Failed to open log file");
                return -1;
            }

            dup2(fd, STDOUT_FILENO);
            dup2(fd, STDERR_FILENO);
            close(fd);

            execvp(command_io[0], command_io);
            perror("[ERROR] execvp failed for io load");
            return 1;
        } else if (pid > 0) {
            int status;
            waitpid(pid, &status, 0);
            printf("[INFO] IO load cycle no %d done! (Exit code : %d)\n", i, status);
        } else {
            perror("[ERROR] Fail to fork io load");
        }
    }
    printf("[SUCCESS] I/O : all %d cycles are done\n", n_io);

    return 0;
}