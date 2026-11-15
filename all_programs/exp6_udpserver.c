#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <arpa/inet.h>
#include <unistd.h>

#define PORT 8080
#define MAX 1024

void translate(char *buffer, char *result)
{
    char temp[MAX], *word;

    strcpy(temp, buffer);
    result[0] = '\0';

    word = strtok(temp, " ,.!?\n");

    while(word != NULL)
    {
        if(strcmp(word, "tbh") == 0)
            strcat(result, "to be honest");

        else if(strcmp(word, "idc") == 0)
            strcat(result, "I don't care");

        else if(strcmp(word, "ig") == 0)
            strcat(result, "I guess");

        else if(strcmp(word, "tbf") == 0)
            strcat(result, "to be fair");

        else if(strcmp(word, "atm") == 0)
            strcat(result, "at the moment");

        else if(strcmp(word, "irl") == 0)
            strcat(result, "in real life");

        else if(strcmp(word, "lol") == 0)
            strcat(result, "laughing out loud");

        else if(strcmp(word, "asap") == 0)
            strcat(result, "as soon as possible");

        else if(strcmp(word, "omg") == 0)
            strcat(result, "oh my God");

        else if(strcmp(word, "ttyl") == 0)
            strcat(result, "talk to you later");

        else if(strcmp(word, "idk") == 0)
            strcat(result, "I don't know");

        else if(strcmp(word, "nvm") == 0)
            strcat(result, "never mind");

        else
            strcat(result, word);

        strcat(result, " ");
        word = strtok(NULL, " ,.!?\n");
    }
}
int main(){
    int sock;
    char buffer[MAX],result[MAX*5];
    struct sockaddr_in server,client;
    socklen_t len = sizeof(client);

    sock = socket(AF_INET,SOCK_DGRAM,0);

    server.sin_family = AF_INET;
    server.sin_port = htons(PORT);
    server.sin_addr.s_addr = INADDR_ANY;

    bind(sock,(struct sockaddr *)&server,sizeof(server));
    printf("UDP Server running....\n");

    recvfrom(sock,buffer,MAX,0,(struct sockaddr *)&client, &len);
    printf("Recived message is: %s",buffer);

    translate(buffer,result);
    sendto(sock, result, strlen(result) + 1, 0,
           (struct sockaddr *)&client, len);

    printf("\nTranslated message sent.\n");
    close(sock);
    return 0;

}