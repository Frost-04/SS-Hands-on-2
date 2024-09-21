/*
============================================================================
Name : 15.c
Author : Gaurav Verma
Description : Write a simple program to send some data from parent to the child process 

Date: 18th Sept, 2024.
============================================================================
*/

#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main() {
    int pipeDescriptor[2];
    pid_t childPid;
    char inputChar;
    char inputString[10];

    if (pipe(pipeDescriptor) == -1) {
        perror("Pipe creation failed");
        exit(EXIT_FAILURE);
    }

    childPid = fork();
    if (childPid == -1) {
        perror("Fork failed");
        exit(EXIT_FAILURE);
    }

    if (childPid == 0) {
        sleep(5);
        close(pipeDescriptor[1]);

        printf("Child process output:\n");
        while (read(pipeDescriptor[0], &inputChar, 1) > 0)
            write(1, &inputChar, 1);

        write(1, "\n", 1);
        close(pipeDescriptor[0]);
    } else {
        printf("Parent process, please enter a message: ");
        scanf("%s", inputString);
        close(pipeDescriptor[0]);
        write(pipeDescriptor[1], inputString, strlen(inputString));
        close(pipeDescriptor[1]);
        wait(0);
    }

    return 0;
}
