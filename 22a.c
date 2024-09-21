/*
============================================================================
Name : 21a.c
Author : Gaurav Verma
Description : Write a program to wait for data to be written into FIFO within 10 seconds, use select
                system call with FIFO.

Date: 19th Sept, 2024.
============================================================================
*/
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/time.h>
#include <unistd.h>
#include <stdio.h>

int main() {
    struct timeval t;
    fd_set fd;
    char *path = "./myfifo";

    mkfifo(path, 0777);  // Create the FIFO

    int f = open(path, O_RDONLY | O_NONBLOCK);  // Open FIFO in non-blocking read mode
    if (f == -1) {
        perror("Error opening FIFO");
        return 1;
    }

    FD_ZERO(&fd);
    FD_SET(f, &fd);

    t.tv_sec = 10;  // Wait for 10 seconds
    t.tv_usec = 0;

    int result = select(f + 1, &fd, NULL, NULL, &t);
    if (result == -1) {
        printf("Error in select\n");
    } else if (result == 0) {
        printf("Timeout\n");
    } else {
        char buf;
        while (read(f, &buf, 1) > 0) {
            write(1, &buf, 1);  // Output data to the terminal
        }
        write(1, "\n", 1);
    }

    close(f);
    return 0;
}
