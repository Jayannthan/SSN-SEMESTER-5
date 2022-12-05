#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<fcntl.h>
#include<netdb.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#define SERVER_TCP_PORT 80
int main(int argc, char * argv[]) {
    int sockfd, len;
    char hostname[20], path[100], request[120], response[1024], newfile[30];
    struct sockaddr_in serveraddr;
    if (argc == 1) 
    {
        printf("Enter URL in command line argument\n");
        return 0;
    }
    int i,j;
    for (i = 0; i < strlen(argv[1]); i++) 
    {
        if (argv[1][i] != '/')
        {
            hostname[i] = argv[1][i];
        }
        else
        {
            break;
        }
    }
    for (i = i, j = 0; i < strlen(argv[1]); i++, j++)
    {
        path[j] = argv[1][i];
    }
    path[j] = '\0';
    strcpy(request, "GET ");
    strcat(request, path);
    strcat(request, " HTTP/1.1\r\nHost: ");
    strcat(request, hostname);
    strcat(request, "\r\n\r\n");
    struct hostent * host = gethostbyname(hostname);
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    serveraddr.sin_family = AF_INET;
    serveraddr.sin_addr = * ((struct in_addr * ) host -> h_addr);
    serveraddr.sin_port = htons(SERVER_TCP_PORT);
    connect(sockfd, (struct sockaddr * ) & serveraddr, sizeof(serveraddr));
    write(sockfd, request, strlen(request));
    len = read(sockfd, response, 1024);
    close(sockfd);
    printf("Enter file name to save: ");
    scanf("%s", newfile);
    FILE * fd = fopen(newfile, "w+");
    fwrite(response, 1, len, fd);
    fclose(fd);
    printf("Downloaded file saved under %s\n", newfile);
    return 0;
}
