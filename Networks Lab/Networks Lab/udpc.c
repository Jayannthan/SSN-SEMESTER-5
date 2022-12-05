#include <netinet/in.h> //structure for storing address information
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include<fcntl.h>

int main(int argc, char const* argv[])
{
    char string[] = "Hello World";
    int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    struct sockaddr_in ser;
    ser.sin_family = AF_INET;
    ser.sin_port = htons(atoi(argv[1]));
    ser.sin_addr.s_addr = INADDR_ANY;
    // connect(sockfd, (struct sockaddr*)&ser, sizeof(ser));
    sendto(sockfd, string, sizeof(string), MSG_CONFIRM, (struct sockaddr*)&ser, sizeof(ser));
    printf("MSG SENT\n");
    int len = sizeof(ser);
    recvfrom(sockfd, string, sizeof(string), MSG_WAITALL, (struct sockaddr*)&ser, &len);
    printf("%s\n", string);

    return 0;
}

