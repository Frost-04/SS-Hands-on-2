/*
============================================================================
Name : 1a.c
Author : Gaurav Verma
Description :   1. Write a separate program (for each time domain) to set a interval timer in 10sec and
                10micro second
                a. ITIMER_REAL
                b. ITIMER_VIRTUAL
                c. ITIMER_PROF

Date: 16th Sept, 2024.
============================================================================
*/
#include <sys/time.h>
#include <signal.h>
#include <unistd.h>
#include <stdio.h>

void main()
{
    struct itimerval intervaltimer;
    printf("Select interval timer\n1:10s\n2:10micros\n");
    int choice;
    scanf("%d", &choice);
    switch (choice)   
    {
    case 1:
        intervaltimer.it_interval.tv_sec = 0;
        intervaltimer.it_interval.tv_usec = 0;
        intervaltimer.it_value.tv_sec = 10;
        intervaltimer.it_value.tv_usec = 0;
        break;
    case 2:
        intervaltimer.it_interval.tv_sec = 0;
        intervaltimer.it_interval.tv_usec = 0;
        intervaltimer.it_value.tv_sec = 0;
        intervaltimer.it_value.tv_usec = 10;
        break;
    default:
        perror("INVALID CHOICE");
        _exit(1);
        break;
    }
    int timerStatus = setitimer(ITIMER_REAL, &intervaltimer, 0);
    if (timerStatus == -1)
        perror("Error while setting an interval timer!");

    while (1)
        ;
}