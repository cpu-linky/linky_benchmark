#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

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

    fd_out = open("dump", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    //TODO: voir o_direct et o_sync 
    //TODO: écrire avant dans un fichier 
    if(fd_out < 0){
        perror("Error opening dump");
        return -1;
    }

    ssize_t written = write(fd_out, buffer, sizeof(buffer));
    if (written != sizeof(buffer)) {
        perror("Writing error");
    }
    close(fd_out);

    // delete file
    if(unlink("dump") < 0){
        perror("Error deleting dump");
        return -1;
    }

    return 0;
}

int main(int argc, char *argv[]) {
    //TODO: add cpu affinity
    if (argc != 2) {
        fprintf(stderr, "Usage : %s <loop>\n", argv[0]);
        return 1;
    }

    int loop = atoi(argv[1]);
    for (int i = 0; i < loop; i++) {
        if (dump_io() != 0) {
            return 1;
        }
    }

    printf("#| Dumped %d * 1MB of random data to dump.bin\n", loop);
    return 0;
}