/*
============================================================================
Name : 12.c
Author : Gaurav Verma
Description : Write a program to create an orphan process. Use kill system call to send SIGKILL signal to
              the parent process from the child process.

Date: 18th Sept, 2024.
============================================================================
*/
#include <unistd.h>
#include <stdio.h>
#include <signal.h>
#include <sys/types.h>
int main()
{
    int pid;
    pid = fork();
    if (pid == 0)
    {
        printf("Child pid= %d\n", getpid());
        printf("Oarent id= %d\n", getppid());
        int status=kill(getppid(),SIGKILL);
        if(status==0){
            printf("Parent process killed, BATMAN created (◣_◢)\n");   
            sleep(10);
        }
        else
            perror("Error while killing parent process!");
        
    }
    else
        while(1); //parent
    return 0;
}