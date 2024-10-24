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

    mkfifo(s, 0777);

    maxFiles = sysconf(_SC_OPEN_MAX);  // maximum number of open files

    printf("Maximum number of files that can be opened: %ld\n", maxFiles);
    
    printf("Maximum size of pipe: %d\n", PIPE_BUF); 

    return 0;
}
