/*
============================================================================
Name : 23.c
Author : Gaurav Verma
Description : Write a program to print the maximum number of files can be opened within a process and
                size of a pipe (circular buffer).

Date: 19th Sept, 2024.
============================================================================
*/
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <limits.h>
#include <stdio.h>

int main() {
    long maxFiles;
    char *s = "./myfifo";

    mkfifo(s, 0777);  // Create FIFO with full permissions

    maxFiles = sysconf(_SC_OPEN_MAX);  // Get maximum number of open files

    printf("Maximum number of files that can be opened: %ld\n", maxFiles);
    
    printf("Maximum size of pipe: %d\n", PIPE_BUF);  // Print the maximum size of the pipe

    return 0;
}
