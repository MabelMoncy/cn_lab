#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#define PORT 8080
#define BUFFER_SIZE 1024
int main(void) {
    int sock;
    char buffer[BUFFER_SIZE] = "TIME";
    struct sockaddr_in server;
    socklen_t len = sizeof(server);

    sock = socket(AF_INET,SOCK_DGRAM,0);

    server.sin_family = AF_INET;
    server.sin_port = htons(PORT);
    server.sin_addr.s_addr = INADDR_ANY;

    sendto(sock, buffer, strlen(buffer), 0,(struct sockaddr *)&server, sizeof(server));
    recvfrom(sock,buffer,BUFFER_SIZE,0,(struct sockaddr *)&server,&len);
    printf("Server Time is %s: ",buffer);
    close(sock);
    return 0;
}
