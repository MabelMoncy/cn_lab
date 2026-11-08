#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080
#define MAX 1024

void translate(char *msg, char *res)
{
    char *shorts[] = {"tbh","idc","ig","tbf","atm","irl",
                      "lol","asap","omg","ttyl","idk","nvm"};
    char *full[] = {"to be honest","I don't care","I guess",
                    "to be fair","at the moment","in real life",
                    "laughing out loud","as soon as possible",
                    "oh my God","talk to you later",
                    "I don't know","never mind"};

    char temp[MAX], *token, word[50];
    int i, found;

    strcpy(temp, msg);
    res[0] = '\0';
    token = strtok(temp, " ,.!?\n");

    while(token != NULL)
    {
        strcpy(word, token);
        for(i = 0; word[i]; i++)
            word[i] = tolower(word[i]);

        found = 0;
        for(i = 0; i < 12; i++)
            if(strcmp(word, shorts[i]) == 0)
            {
                strcat(res, full[i]);
                found = 1;
                break;
            }

        if(!found) strcat(res, token);
        strcat(res, " ");
        token = strtok(NULL, " ,.!?\n");
    }
}

int main()
{
    int s;
    char buf[MAX], res[MAX * 5];
    struct sockaddr_in server, client;
    socklen_t len = sizeof(client);

    s = socket(AF_INET, SOCK_DGRAM, 0);
    server.sin_family = AF_INET;
    server.sin_port = htons(PORT);
    server.sin_addr.s_addr = INADDR_ANY;

    bind(s, (struct sockaddr *)&server, sizeof(server));
    printf("UDP Server Running...\n");

    recvfrom(s, buf, MAX, 0, (struct sockaddr *)&client, &len);
    printf("Received: %s\n", buf);

    translate(buf, res);
    sendto(s, res, strlen(res) + 1, 0,
           (struct sockaddr *)&client, len);

    printf("Translated message sent.\n");
    close(s);
    return 0;
}