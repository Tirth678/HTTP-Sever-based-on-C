#include<stdio.h>
#include<stdlib.h>
#include<sys/stat.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#define PORT 8000
#define MAXIMUM_REQUET_SIZE 2048
#define ROOT "./src"
void handling(int sock){
    char 
}
int main(){
    int ServerSock, clientSock;
    struct sockaddr_in serverAddr, clientAddr;
    socklen_t  lenAddr = sizeof(struct sockaddr_in);
    
    ServerSock = socket(AF_INET, SOCK_STREAM, 0);
    if(ServerSock == -1){
        perror("Socket failed badly...");
        exit(EXIT_FAILURE);
    }

    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = INADDR_ANY;
    serverAddr.sin_port = htons(PORT);

    if(bind(ServerSock, (struct sockAddr *)&serverAddr, sizeof(serverAddr)) == -1){
        perror("Binding or binding failed\n");
        exit(EXIT_FAILURE);
    }
    if (listen(ServerSock, 10) < 0){
        perror("Bad ear, failed to listen...");
        exit(EXIT_FAILURE);
    }
    printf("Listing to port...%d", PORT);

    while(1){
        clientSock = accept(ServerSock, (struct sockaddr *)&clientAddr, &lenAddr);
        if (clientSock < 0){
            perror("Proposal declined...");
            exit(EXIT_FAILURE);
        }
        // handling(clientSock);
    }
    return 0;

}