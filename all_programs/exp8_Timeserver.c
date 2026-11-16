#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <time.h>
#define PORT 8080
#define BUFFER_SIZE 1024
int main(void) {
    int sock;
    char buffer[BUFFER_SIZE];
    struct sockaddr_in server,client;
    socklen_t len = sizeof(client);

    sock = socket(AF_INET,SOCK_DGRAM,0);

    server.sin_family = AF_INET;
    server.sin_port = htons(PORT);
    server.sin_addr.s_addr = INADDR_ANY;

    bind(sock,(struct sockaddr *)&server,sizeof(server));
    printf("\nUDP server running....");
    while(1){
        recvfrom(sock,buffer,BUFFER_SIZE,0,(struct sockaddr *)&client, &len);
        time_t current_time;
        time(&current_time);
        strcpy(buffer,ctime(&current_time));
        sendto(sock,buffer,strlen(buffer),0,(struct sockaddr *)&client,len);
        close(sock);
        return 0;
    }
}
