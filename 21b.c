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

#define FIFO1 "/tmp/fifo1"  // Read FIFO
#define FIFO2 "/tmp/fifo2"  // Write FIFO

int main() {
    char message[100], reply[100];

    // Create FIFOs if they do not exist
    mkfifo(FIFO1, 0666);
    mkfifo(FIFO2, 0666);

    // Read message from prog1
    int read_fd = open(FIFO1, O_RDONLY);
    if (read_fd < 0) {
        perror("open read_fd");
        exit(1);
    }

    read(read_fd, message, sizeof(message));
    printf("Received message from prog1: %s\n", message);
    close(read_fd);

    // Write reply to prog1
    int write_fd = open(FIFO2, O_WRONLY);
    if (write_fd < 0) {
        perror("open write_fd");
        exit(1);
    }

    printf("Enter reply to prog1: ");
    fgets(reply, 100, stdin);
    write(write_fd, reply, strlen(reply) + 1);
    close(write_fd);

    return 0;
}
