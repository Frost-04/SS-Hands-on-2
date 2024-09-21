/*
============================================================================
Name : 18.c
Author : Gaurav Verma
Description : Write a program to find out total number of directories on the pwd.
              execute ls -l | grep ^d | wc ? Use only dup2.  

Date: 18th Sept, 2024.
============================================================================
*/

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main() {
    int pipefd[2], pipefd2[2];
    pid_t cid, cid2;

    if (pipe(pipefd) == -1) {
        printf("ERROR");
        return 1;
    }
    if (pipe(pipefd2) == -1) {
        printf("ERROR");
        return 1;
    }

    cid = fork();
    if (cid == 0) {
        cid2 = fork();
        if (cid2 == 0) {
            close(pipefd[0]);  // Close read end of pipefd
            close(pipefd[1]);  // Close write end of pipefd
            close(pipefd2[1]); // Close write end of pipefd2

            dup2(pipefd2[0], 0); // Redirect stdin to pipefd2
            execl("/usr/bin/wc", "wc", NULL); // Run wc
        } else {
            close(pipefd[1]);  // Close write end of pipefd
            close(pipefd2[0]); // Close read end of pipefd2

            dup2(pipefd[0], 0); // Redirect stdin to pipefd
            dup2(pipefd2[1], 1); // Redirect stdout to pipefd2
            execl("/usr/bin/grep", "grep", "^d", NULL); // Run grep
        }
    } else {
        close(pipefd2[0]); // Close read end of pipefd2
        close(pipefd2[1]); // Close write end of pipefd2
        close(pipefd[0]);  // Close read end of pipefd

        dup2(pipefd[1], 1); // Redirect stdout to pipefd
        execl("/usr/bin/ls", "ls", "-l", NULL); // Run ls
    }

    return 0;
}
