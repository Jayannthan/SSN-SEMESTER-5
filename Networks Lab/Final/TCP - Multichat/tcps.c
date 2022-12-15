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

	struct sockaddr_in server;
	server.sin_family=AF_INET;
	server.sin_addr.s_addr=INADDR_ANY;
	server.sin_port=htons(atoi(argv[1]));

	int sockfd=socket(AF_INET,SOCK_STREAM,0);
	bind(sockfd,(struct sockaddr*)&server,sizeof(server));
	listen(sockfd,1);
	
	

	char string[100];
	while(1)
	{
		int clientsocket=accept(sockfd,NULL,NULL);
		int pid=fork();
		if (pid>0)
		{
			close(sockfd);
			while(1)
			{
				read(clientsocket,string,sizeof(string));
				printf("\n\nString %d:%s\n",clientsocket, string );

				printf("Enter string:");
				gets(string);

				write(clientsocket,string,sizeof(string));
			}
		}
		
	}
	

	return 0;
}