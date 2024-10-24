/*
============================================================================
Name : 33client.c
Author : Gaurav Verma
Description :  Write a program to communicate between two machines using socket.

Date: 21th Sept, 2024.
============================================================================
*/

#include <sys/types.h>  
#include <sys/socket.h> 
#include <netinet/ip.h> 
#include <stdio.h>      
#include <unistd.h>     
void main()
{
    int socktd=socket(AF_INET,SOCK_STREAM,0);
    if(socktd==-1){
        perror("Error when creating socket");
    }
    printf("Socket created\n");

    // assigning server info
    struct sockaddr_in address;
    address.sin_addr.s_addr=htonl(INADDR_ANY);
    address.sin_family=AF_INET;
    address.sin_port=htons(8080);

    //make connection to the server
    int connectionS = connect(socktd, (struct sockaddr *)&address, sizeof(address));

    if(connectionS==-1){
        perror("Error while establishing Connection");
    }
    
    printf("Connection with server established");

    char buf[100];
    //read from server
    read(socktd,buf,100);
    printf("Data from server: %s\n",buf);

    printf("Write massage for server: ");
    scanf("%[^\n]",buf);

    write(socktd,buf,sizeof(buf));
    printf("Data sent to server");

    //closing socket
    close(socktd);
}