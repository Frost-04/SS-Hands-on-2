/*
============================================================================
Name : 11.c
Author : Gaurav Verma
Description : Write a program to ignore a SIGINT signal then reset the default action of the SIGINT signal -
              use sigaction system call.  

Date: 18th Sept, 2024.
============================================================================
*/
#include <stdio.h>
#include <signal.h>
#include <unistd.h>

// Custom signal handler for SIGINT to ignore the signal
void ignore_sigint(int sig) {
    printf("SIGINT ignored! Press Ctrl+C again to reset the default action.\n");
}

int main() {
    struct sigaction sa;

    // Step 1: Ignore the SIGINT signal
    sa.sa_handler = ignore_sigint;      // Set custom signal handler
    sigemptyset(&sa.sa_mask);           // Initialize signal set to empty
    sa.sa_flags = 0;                    // No special flags
    sigaction(SIGINT, &sa, NULL);       // Set the action for SIGINT

    printf("SIGINT is being ignored. Press Ctrl+C.\n");
    sleep(5);  // Allow time for the user to press Ctrl+C

    // Step 2: Reset SIGINT to default behavior
    sa.sa_handler = SIG_DFL;            // Reset to default action
    sigaction(SIGINT, &sa, NULL);       // Set default action for SIGINT

    printf("SIGINT is now back to default action. Press Ctrl+C again.\n");
    sleep(10);  // Allow time for the user to press Ctrl+C again and see the default action

    return 0;
}
