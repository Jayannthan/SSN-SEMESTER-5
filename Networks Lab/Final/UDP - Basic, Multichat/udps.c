#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <sys/socket.h>

int main(int argc, char const *argv[])
{
	if (argc<2)
	{
		printf("Enter port number in terminal\n");
		return 0;
	}

	struct sockaddr_in server,client;
	server.sin_family=AF_INET;
	server.sin_addr.s_addr=INADDR_ANY;
	server.sin_port=htons(atoi(argv[1]));

	int sockfd=socket(AF_INET,SOCK_DGRAM,0);
	bind(sockfd, (struct sockaddr*)&server, sizeof(server));
	char string[100];
	int length=sizeof(client);
	while(1)
	{
		recvfrom(sockfd,string,sizeof(string),MSG_WAITALL,(struct sockaddr*)&client,&length);
		printf("String:%s\n",string );

		printf("Enter string:\n");
		gets(string);

		sendto(sockfd,string,sizeof(string),MSG_CONFIRM,(struct sockaddr*)&client,length);
	}
	

	return 0;
};