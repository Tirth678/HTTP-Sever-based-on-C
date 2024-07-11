#include<stdio.h>
#include<stdlib.h>
#include<sys/stat.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<fcntl.h>
#include<unistd.h>
#include<string.h>
#define PORT 8000
#define MAXIMUM_REQUET_SIZE 2048
#define ROOT "./src"
void handling(int sock){
    char request[MAXIMUM_REQUET_SIZE] = {0};
    recv(sock, request, MAXIMUM_REQUET_SIZE, 0);

    char method[10], path[25], protocol[20];
    sscanf(request, "%s%s%s", method, path, protocol);
    char filePath[225];
    sprintf(filePath, "%s%s", ROOT, path);
    if(strcmp(path, "/") == 0){
        sprintf(filePath, "%s/index.html", ROOT);
    }
    int file = open(filePath, O_RDONLY);
    if(file == -1){
        char res[] = "HTTP/1.1 404 NOT FOUND\r\n\r\n";
        send(sock, res, strlen(res), 0);
    } else{
        char res[] = "HTTP/1.1 2000 OK\r\n\r\n";
        send(sock, res, strlen(res), 0);

        char buf[1024];
        ssize_t readBytes;
        while((readBytes = read(file, buf, sizeof(buf))) > 0){
            send(sock, buf, readBytes, 0);
        }
        close(file);
    }
    close(sock);

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
        perror("Binding failed\n");
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
        handling(clientSock);
    }
    return 0;

}