/*
============================================================================
Name : 9.c
Author : Gaurav Verma
Description : . Write a program to ignore a SIGINT signal then reset the default action of the SIGINT
                signal - Use signal system call.

Date: 17th Sept, 2024.
============================================================================
*/
#include <stdio.h>
#include <signal.h>
#include <unistd.h>

// Function to handle SIGINT and ignore it
void ignore_sigint() {
    printf("SIGINT ignored! Press Ctrl+C again to reset the default action.\n");
}

int main() {
    // Step 1: Set the signal handler to ignore SIGINT
    signal(SIGINT, ignore_sigint);

    printf("SIGINT is being ignored. Press Ctrl+C.\n");

    // Sleep to allow time for the user to press Ctrl+C
    sleep(5);

    // Step 2: Reset the signal handler for SIGINT to its default action
    signal(SIGINT, SIG_DFL);

    printf("SIGINT is now back to default action. Press Ctrl+C again.\n");

    // Sleep to allow time for the user to press Ctrl+C again and see the default action
    sleep(10);

    return 0;
}
