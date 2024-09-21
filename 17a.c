/*
============================================================================
Name : 17a.c
Author : Gaurav Verma
Description : Write a program to execute ls -l | wc.
              a. use dup
              b. use dup2
              c. use fcntl 

Date: 18th Sept, 2024.
============================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    int pipefd[2];
    pid_t pid;

    if (pipe(pipefd) == -1) {
        perror("Pipe creation failed");
        exit(EXIT_FAILURE);
    }

    pid = fork();
    if (pid == -1) {
        perror("Fork failed");
        exit(EXIT_FAILURE);
    }

    if (pid == 0) {
        close(pipefd[0]);
        close(1);  // Close stdout
        dup(pipefd[1]);  // Duplicate pipe write end to stdout
        execlp("ls", "ls", "-l", NULL);  // Execute 'ls -l'
    } else {
        close(pipefd[1]);
        close(0);  // Close stdin
        dup(pipefd[0]);  // Duplicate pipe read end to stdin
        execlp("wc", "wc", NULL);  // Execute 'wc'
    }

    return 0;
}
