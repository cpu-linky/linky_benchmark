#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>

int main() {
    char *command_cpu[] = {"turbostat", "--quiet", "--interval", "1", "bin/cpu_load", "10000000", NULL};
    char *command_mem[] = {"turbostat", "--quiet", "--interval", "1", "bin/memory_load", "10000000", NULL};
    char *command_io[] = {"turbostat", "--quiet", "--interval", "1", "bin/io_load", "300", NULL};

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