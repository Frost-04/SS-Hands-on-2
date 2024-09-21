/*
============================================================================
Name : 21b.c
Author : Gaurav Verma
Description : Write a program to wait for data to be written into FIFO within 10 seconds, use select
                system call with FIFO.

Date: 19th Sept, 2024.
============================================================================
*/

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

int main() {
    int f;
    char *s = "./myfifo";
    
    mkfifo(s, 0777);  // Create FIFO with full permissions

    f = open(s, O_WRONLY | O_NONBLOCK);  // Open FIFO for writing in non-blocking mode

    if (f == -1) {
        perror("Error opening FIFO");
        return 1;
    }

    char *st;
    long size = 100;
    printf("Enter message:\n");

    int len = getline(&st, &size, stdin);  // Read message from user
    write(f, st, len);  // Write message to FIFO

    close(f);  // Close the FIFO
    return 0;
}
