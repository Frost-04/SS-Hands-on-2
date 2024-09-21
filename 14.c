/*
============================================================================
Name : 14.c
Author : Gaurav Verma
Description : Write a simple program to create a pipe, write to the pipe, read from pipe and display on
              the monitor. 

Date: 18th Sept, 2024.
============================================================================
*/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main() {
    int myPipe[2];
    char buffer[10];
    char character;

    if (pipe(myPipe) == -1) {
        printf("Pipe failed\n");
        return 1;
    }

    printf("Enter a string of 10 characters: ");
    scanf("%s", buffer);

    write(myPipe[1], buffer, 10);
    write(myPipe[1], "\n", 1);

    close(myPipe[1]);

    printf("Reading from pipe:\n");
    while (read(myPipe[0], &character, 1) > 0) {
        write(1, &character, 1);
    }

    close(myPipe[0]);

    return 0;
}
