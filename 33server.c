/*
============================================================================
Name : 33server.c
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
    int socktd = socket(AF_INET, SOCK_STREAM, 0);
    if (socktd == -1)
    {
        perror("Erroe when creating socket");
    }
    printf("server Socket created\n");

    // server info
    struct sockaddr_in server, client;
    server.sin_addr.s_addr = htonl(INADDR_ANY); // host to network long
    server.sin_family = AF_INET;
    server.sin_port = htons(8080);

    int bindS = bind(socktd, (struct sockaddr *)&server, sizeof(server));
    if (bindS == -1)
    {
        perror("Error while binding name to socket!");
        _exit(0);
    }
    printf("Binding to server socket was successful!\n");

    // listen for connection
    int listenS = listen(socktd, 2);
    if (listenS == -1)
    {
        perror("Error while trying to listen to Connections");
        _exit(0);
    }
    printf("Listning from Connection ");

    int client_size = (int)sizeof(client);
    int connectionfd = accept(socktd, (struct sockaddr *)&client, &client_size);
    if (connectionfd == -1)
    {
        perror("Error while accepting Connection");
        _exit(0);
    }
    else
    {
        char buf[100];
        printf("Write massage form server to client: ");
        scanf("%[^\n]", buf);
        // write fron server to connection fd
        write(connectionfd, buf, sizeof(buf));

        read(connectionfd, buf, 100);
        printf("Data from client: %s\n", buf);
    }

    // closing socket
    close(socktd);
}