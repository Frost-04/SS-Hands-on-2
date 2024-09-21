/*
============================================================================
Name : 13a.c
Author : Gaurav Verma
Description : Write two programs: first program is waiting to catch SIGSTOP signal, the second program
              will send the signal (using kill system call). Find out whether the first program is able to catch
              the signal or not 

Date: 18th Sept, 2024.
============================================================================
*/

#include <unistd.h>
#include <stdio.h>
#include <signal.h>
#include <sys/types.h>
#include <stdlib.h>
void print()
{
    printf("Received SIGSTOP");
}
void main()
{

    __sighandler_t status = signal(SIGSTOP,print);
    if (status == SIG_ERR)
        perror("Error while assigning signal handler");
    sleep(10);
}

/* 
    A program cannot catch a SIGSTOP signal.We can conclude this by observing that the customHandler function is never executed and instead the program is terminated !
    Two signals that cannot be caught or ignored are
    SIGSTOP
    SIGKILL
*/