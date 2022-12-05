#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <fcntl.h>

int main(int argc, char const *argv[])
{
	if (argc<2)
	{
		printf("Required port no.\n");
		return 0;
	}
	int sockfd=socket(AF_INET,SOCK_STREAM,0);
	struct sockaddr_in serveraddr,cliaddr;
	serveraddr.sin_family=AF_INET;
	serveraddr.sin_port=htons(atoi(argv[1]));
	serveraddr.sin_addr.s_addr=INADDR_ANY;
	connect(sockfd, (struct sockaddr*)&serveraddr, sizeof(serveraddr));
	char string[100];
	recv(sockfd, string, sizeof(string), 0);
    printf("%s\n", string);

	return 0;
}