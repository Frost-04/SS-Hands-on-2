/*
============================================================================
Name : 16.c
Author : Gaurav Verma
Description : Write a program to send and receive data from parent to child vice versa. Use two way
              communication.

Date: 18th Sept, 2024.
============================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

int main() {
    int ptc[2], ctp[2];  // parent-to-child (ptc) and child-to-parent (ctp)
    pid_t cpid;  // child process id
    char p_msg[20], c_msg[20], ch;

    if (pipe(ptc) == -1 || pipe(ctp) == -1) {
        perror("Pipe failed");
        exit(EXIT_FAILURE);
    }

    cpid = fork();
    if (cpid == -1) {
        perror("Fork failed");
        exit(EXIT_FAILURE);
    }

    if (cpid == 0) {
        close(ptc[1]);
        close(ctp[0]);
        sleep(5);
        printf("Child: Receiving message from parent...\n");
        while (read(ptc[0], &ch, 1) > 0)
            write(1, &ch, 1);
        
        printf("\nChild: Sending message to parent...\n");
        strcpy(c_msg, "Hello Parent");
        write(ctp[1], c_msg, strlen(c_msg));

        close(ptc[0]);
        close(ctp[1]);
    } else {
        close(ptc[0]);
        close(ctp[1]);

        printf("Parent: Enter a message for the child: \n");
        scanf("%s", p_msg);

        write(ptc[1], p_msg, strlen(p_msg));
        close(ptc[1]);
        sleep(5);
        printf("Parent: Receiving message from child...\n");
        while (read(ctp[0], &ch, 1) > 0)
            write(1, &ch, 1);
        
        printf("\n");
        close(ctp[0]);
        wait(0);
    }

    return 0;
}
