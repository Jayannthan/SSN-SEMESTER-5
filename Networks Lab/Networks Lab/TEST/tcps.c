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
	struct sockaddr_in serveraddr;
	serveraddr.sin_family=AF_INET;
	serveraddr.sin_port=htons(atoi(argv[1]));
	serveraddr.sin_addr.s_addr=INADDR_ANY;
	bind(sockfd,(struct sockaddr_in*)&serveraddr,sizeof(serveraddr));
	listen(sockfd,1);

	int clientsocket=accept(sockfd,NULL,NULL);
	char string[] = "Hello World";
	send(clientsocket, string, sizeof(string), 0);
	printf("%s\n",string );

	return 0;
}