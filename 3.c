/*
============================================================================
Name : 3.c
Author : Gaurav Verma
Description : Write a program to set (any one) system resource limit. Use setrlimit system call. 

Date: 16th Sept, 2024.
============================================================================
*/
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <unistd.h>

void print(char *text, rlim_t current, rlim_t maxlim, char *unit)
{
    printf("%s - \n", text);

    printf("\tSoft Limit: ");
    if (current == RLIM_INFINITY)
        printf("Unlimited\n");
    else
        printf("%ld %s\n", current, unit);

    printf("\tHard Limit: ");
    if (maxlim == RLIM_INFINITY)
        printf("Unlimited\n");
    else
        printf("%ld %s\n", maxlim, unit);
}

int main() {
    // Declare a rlimit structure to hold the new limit values
    struct rlimit rl;
    int status;             // Determines the success of the `getrlimit` call
    struct rlimit resLim; // Holds the hard & soft limits for a resource

    // Set a new CPU time limit (in seconds)
    rl.rlim_cur = 5;  // Soft limit (5 seconds)
    rl.rlim_max = 10; // Hard limit (10 seconds)

    status = getrlimit(RLIMIT_CPU, &resLim);
    if (status == -1)
        perror("Error while getting RLIMIT_CPU!");
    else
        print("Default CPU time limit:", resLim.rlim_cur, resLim.rlim_max, "seconds");

    // Use setrlimit to set the CPU time limit (RLIMIT_CPU)
    if (setrlimit(RLIMIT_CPU, &rl) == -1) {
        perror("setrlimit failed");
        return 1;
    }
    status = getrlimit(RLIMIT_CPU, &resLim);
    if (status == -1)
        perror("Error while getting RLIMIT_CPU!");
    else
        print("Changed CPU time limit:", resLim.rlim_cur, resLim.rlim_max, "seconds");

   

    

    return 0;
}
