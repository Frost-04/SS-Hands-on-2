/*
============================================================================
Name : 21a.c
Author : Gaurav Verma
Description : Write two programs so that both can communicate by FIFO -Use two way communications.



Date: 19th Sept, 2024.
============================================================================
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>

#define FIFO1 "/tmp/fifo1"  // Write FIFO
#define FIFO2 "/tmp/fifo2"  // Read FIFO

int main() {
    char message[100], reply[100];
    
    // Create FIFOs if they do not exist
    mkfifo(FIFO1, 0666);
    mkfifo(FIFO2, 0666);

    // Write message to prog2
    int write_fd = open(FIFO1, O_WRONLY);
    if (write_fd < 0) {
        perror("open write_fd");
        exit(1);
    }

    printf("Enter message for prog2: ");
    fgets(message, 100, stdin);
    write(write_fd, message, strlen(message) + 1);
    close(write_fd);

    // Read reply from prog2
    int read_fd = open(FIFO2, O_RDONLY);
    if (read_fd < 0) {
        perror("open read_fd");
        exit(1);
    }

    read(read_fd, reply, sizeof(reply));
    printf("Received reply from prog2: %s\n", reply);
    close(read_fd);

    return 0;
}
