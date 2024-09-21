/*
============================================================================
Name : 10a.c
Author : Gaurav Verma
Description : Write a separate program using sigaction system call to catch the following signals.
              a. SIGSEGV
              b. SIGINT
              c. SIGFPE

Date: 17th Sept, 2024.
============================================================================
*/
#include <stdio.h>
#include <unistd.h>
#include <signal.h>
void print(){
    printf("Caught SIGSEGV\n");
}
void main()
{
    int status;
    struct sigaction action;
    
    action.sa_handler=print;//function that replace default action of signal SIGSEGV
    action.sa_flags=0;
    status = sigaction(SIGSEGV,&action,NULL);
    
    if (status == -1)
        perror("Error while assigning signal handler!");

    else
        raise(SIGSEGV);
}