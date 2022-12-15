#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <math.h>
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
	int clientsocket=accept(sockfd,NULL,NULL);
	

	char ip[100];



	read(clientsocket,ip,sizeof(ip));
	printf("IP RCVD\n");
	int n;
	read(clientsocket,&n,sizeof(n));
	printf("N RCVD\n");

	printf("\nIP recvd:%s\n",ip);

	in_addr_t ipv4=htonl(inet_addr(ip));
	printf("\nIPv4(bin):%u\n",ipv4);
	write(clientsocket,&ipv4,sizeof(ipv4));

	int n1,n2,n3,n4;
	sscanf(ip, "%d.%d.%d.%d/%d", &n1, &n2, &n3, &n4,&n);
	printf("\n\n%d %d %d %d ",n1,n2,n3,n4);
	if (ipv4!=-1)
	{
		int mask[32];
		int i;
		for (i = 0; i < n; ++i)
		{
			mask[i]=1;
		}
		for (;i < 32; ++i)
		{
			mask[i]=0;
		}
		
	}

	return 0;
}