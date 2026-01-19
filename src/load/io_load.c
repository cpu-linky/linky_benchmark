#include <stdio.h>

// dump a 1Mo buffer of random data (/dev/urandom) into a dump file
int dump_io(){
    FILE *fp;
    FILE *fp2;
    char buffer[1024*1024];

    fp = fopen("/dev/urandom", "rb");
    if(fp == NULL){
        perror("Error opening /dev/urandom");
        return -1;
    }

    size_t result = fread(buffer, 1, sizeof(buffer), fp);
    if (result != sizeof(buffer)) {
        perror("Reading error"); 
    }
    fclose(fp);

    fp2 = fopen("dump.bin", "wb");
    if(fp2 == NULL){
        perror("Error opening dump.bin");
        fclose(fp);
        return -1;
    }
        
    fwrite(buffer, 1, sizeof(buffer), fp2);
    fclose(fp2);
    return 0;
}