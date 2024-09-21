/*
============================================================================
Name : 8c.c
Author : Gaurav Verma
Description : Write a separate program using signal system call to catch the following signals.
               a. SIGSEGV
               b. SIGINT
               c. SIGFPE
               d. SIGALRM (use alarm system call)
               e. SIGALRM (use setitimer system call)
               f. SIGVTALRM (use setitimer system call)
               g. SIGPROF (use setitimer system call)


Date: 17th Sept, 2024.
============================================================================
*/
#include <stdio.h>
#include <unistd.h>
#include <signal.h>
void print()
{
    printf("SIGFPE caught\n");
    _exit(0);
}

void main()
{
    __sighandler_t status;

    status = signal(SIGFPE, print);
    if (status == SIG_ERR)
        perror("Error while assigning signal handler!");
        
    else
    {
        raise(SIGFPE);
    }
}