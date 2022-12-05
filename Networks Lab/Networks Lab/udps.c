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
	char string[100];
	int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
	struct sockaddr_in ser, cli;
	ser.sin_family = AF_INET;
	ser.sin_port = htons(atoi(argv[1]));
	ser.sin_addr.s_addr = INADDR_ANY;
	bind(sockfd, (struct sockaddr*)&ser, sizeof(ser));
	// listen(sockfd, 1);
	// int clientsocket = accept(sockfd, NULL, NULL);
	while(1){
	int len = sizeof(cli);
	recvfrom(sockfd, string, sizeof(string), MSG_WAITALL, (struct sockaddr*)&cli, &len);
	printf("%s\n", string);
	strcpy(string, "abcd");
	sendto(sockfd, string, sizeof(string), MSG_CONFIRM, (struct sockaddr*)&cli, len);
	printf("MSG SENT\n");
	}

	return 0;
}

