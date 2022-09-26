#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <netdb.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <fcntl.h>

int main(int argc, char const *argv[])
{
	int port = atoi(argv[1]);
	int sockfd, ssize;
	char buffer[1024];
	struct sockaddr_in serveraddr;
	sockfd = socket(AF_INET, SOCK_DGRAM, 0);
	if (sockfd == -1)
	{
		printf("SOCKET creation failed !!\n");
		exit(0);
	}
	else
		printf("socket creation succesful\n");
	serveraddr.sin_family = AF_INET;
	serveraddr.sin_addr.s_addr = inet_addr("127.0.0.1");
	serveraddr.sin_port = htons(port);
	int connected = 1;
	char strData[255];
	while (connected)
	{
		ssize = sizeof(serveraddr);
		printf("\nEnter data to send to server:");
		scanf(" %[^\n]s", buffer);
		sendto(sockfd, buffer, sizeof(buffer), 0, (struct sockaddr *)&serveraddr, ssize);
		recvfrom(sockfd, strData, sizeof(strData), 0, (struct sockaddr *)&serveraddr, &ssize);
		if (strcmp(buffer, "exit") == 0)
		{
			connected = 0;
		}
		else
		{
			printf("\nMessage from server: %s\n", strData);
		}
	}
	close(sockfd);
}
