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
	int sockfd, csize, arr[30], pre = 0, flag, p, i;
	char buffer[1024];
	struct sockaddr_in serveraddr, clientaddr;
	fd_set readfds;
	for (int i = 0; i < 30; i++)
		arr[i] = 0;

	sockfd = socket(AF_INET, SOCK_DGRAM, 0);
	if (sockfd == -1)
	{
		printf("SOCKET creation failed !!\n");
		exit(0);
	}
	else
		printf("socket creation succesful\n");

	serveraddr.sin_family = AF_INET;
	serveraddr.sin_addr.s_addr = INADDR_ANY;
	serveraddr.sin_port = htons(port);

	if ((bind(sockfd, (struct sockaddr *)&serveraddr, sizeof(serveraddr))) != 0)
	{
		printf("socket binding failed\n");
		exit(0);
	}
	else
	{
		printf("socket binding successful\n");
	}

	bzero(&serveraddr, sizeof(struct sockaddr_in));

	FD_ZERO(&readfds);
	while (1)
	{
		FD_SET(sockfd, &readfds);
		csize = sizeof(clientaddr);
		select(sockfd + 1, &readfds, NULL, NULL, NULL);
		recvfrom(sockfd, buffer, 1024, 0, (struct sockaddr *)&clientaddr, &csize);
		p = ntohs(clientaddr.sin_port);
		flag = 0;
		for (i = 0; i < 30; i++)
			if (arr[i] == p)
			{
				p = i + 1;
				flag = 1;
				break;
			}
		if (flag == 0)
		{
			arr[pre] = p;
			pre++;
			p = pre;
		}
		if (strcmp(buffer, "exit") == 0)
		{
			printf("\n Client %d closed the chat\n", p);
		}
		else
		{
			printf("\nMessage from Client %d: %s\n", p, buffer);
			csize = sizeof(serveraddr);
			char strData[255];
			printf("\nEnter reply:");
			scanf(" %[^\n]s", strData);
			sendto(sockfd, strData, sizeof(strData), 0, (struct sockaddr *)&clientaddr, csize);
			// printf("Message sent: %s\n", strData);
		}
	}
	close(sockfd);
	return 0;
}
