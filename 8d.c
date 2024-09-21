/*
============================================================================
Name : 8d.c
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
    printf("SIGALRM caught\n");
    _exit(0);
}

void main()
{
    __sighandler_t status;
    int time=3;
    alarm(time);
    status = signal(SIGALRM, (void *)print);
    
    if (status == SIG_ERR)
        perror("Error while assigning signal handler!");

    else
    {
        for(int i=0;i<time;i++)
        {
            sleep(1);
            printf("Time Passed : %d sec \t alarm at : %d\n",i+1,time);
        }
    }
}