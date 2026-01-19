#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

// dump a 1Mo buffer of random data (/dev/urandom) into a dump file
int dump_io(){
    int fd_in, fd_out;
    char buffer[1024*1024];

    fd_in = open("/dev/urandom", O_RDONLY);
    if(fd_in < 0){
        perror("Error opening /dev/urandom");
        return -1;
    }

    ssize_t result = read(fd_in, buffer, sizeof(buffer));
    if (result != sizeof(buffer)) {
        perror("Reading error");
    }
    close(fd_in);

    fd_out = open("dump.bin", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if(fd_out < 0){
        perror("Error opening dump.bin");
        return -1;
    }

    ssize_t written = write(fd_out, buffer, sizeof(buffer));
    if (written != sizeof(buffer)) {
        perror("Writing error");
    }
    close(fd_out);
    return 0;
}