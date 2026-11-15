#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>

#define PORT 8080
#define MAX 1024

int main(){

    int sock;
    char message[MAX],buffer[MAX * 5];

    struct sockaddr_in server;
    socklen_t len = sizeof(server);

    sock = socket(AF_INET,SOCK_DGRAM,0);

    server.sin_family = AF_INET;
    server.sin_port = htons(PORT);
    server.sin_addr.s_addr = INADDR_ANY;

    printf("Enter the message to be translate: ");
    fgets(message,MAX,stdin);

    sendto(sock,message,strlen(message)+1,0,(struct sockaddr *)&server,len);
    recvfrom(sock,buffer,sizeof(buffer),0,(struct sockaddr *)&server,&len);
    printf("The translated message is:  \n%s",buffer);

    close(sock);
    return 0;

}
