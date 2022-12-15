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
	connect(sockfd,(struct sockaddr*)&server,sizeof(server));

	
	char ip[100];
	
	printf("Enter IPv4(a.b.c.d):");
	gets(ip);
	int n;
	printf("Enter n:");
	scanf("%d",&n);
	
	printf("IP:%s\n",ip);
	printf("n:%d\n",n);

	write(sockfd,ip,sizeof(ip));
	printf("IP SENT\n");
	write(sockfd,&n,sizeof(n));
	printf("N SENT\n");
	

	in_addr_t ipv4;
	read(sockfd,&ipv4,sizeof(ipv4));
	if (ipv4==-1)
	{
		printf("INVALID IP\n");
	}
	else
	{
		printf("IP(bin):%u\n", ipv4);
	}




	
	
	return 0;
}