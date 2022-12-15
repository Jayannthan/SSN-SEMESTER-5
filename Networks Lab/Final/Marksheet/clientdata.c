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
	connect(sockfd,(struct sockaddr*)&server,sizeof(server));

	while(1)
	{
		int roll,marks[5];
	
		read(sockfd,&roll,sizeof(roll));
		printf("Roll no:%d\n\n",roll);
	
		for (int i = 0; i < 5; ++i)
		{
			printf("Enter marks %d:",i+1);
			scanf(" %d",&marks[i]);
			write(sockfd,&marks[i],sizeof(marks[i]));
		}
	}
	return 0;
}