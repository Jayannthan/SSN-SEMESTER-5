#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <sys/socket.h>

typedef struct ARP
{
	int type;
	char src_ip[20],des_ip[20],src_mac[20],des_mac[20],string[20];
} ARP;

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
	listen(sockfd,5);

	ARP packet;
	packet.type=0;
	printf("\nEnter Server IP:");
	scanf(" %s",packet.src_ip);
	printf("\nEnter Server MAC:");
	scanf(" %s",packet.src_mac);
	printf("\nEnter Destination IP:");
	scanf(" %s",packet.des_ip);
	strcpy(packet.des_mac,"00:00:00:00:00:00");

	printf("\n\nSending packet:%d|%s|%s|%s|%s\n\n",packet.type,packet.src_mac,packet.src_ip,packet.des_mac,packet.des_ip);

	while(1)
	{
		int clientsocket=accept(sockfd,NULL,NULL);
		if (clientsocket!=-1)
		{
			printf("\nNew Connection\n");
			int pid=fork();
			if (pid==0)
			{
				close(sockfd);
				write(clientsocket,&packet,sizeof(packet));
				read(clientsocket,&packet,sizeof(packet));
				if (packet.type==1)
				{
					printf("\nIP MATCH FOUND");
					printf("\n\nReceived packet:%d|%s|%s|%s|%s",packet.type,packet.des_mac,packet.des_ip,packet.src_mac,packet.src_ip);
					packet.type=3;
					printf("\nEnter data to send:");
					scanf(" %s",packet.string);
					write(clientsocket,&packet,sizeof(packet));
					printf("\n\nFinal packet sent with data:%d|%s|%s|%s|%s|%s\n\n",packet.type,packet.src_mac,packet.src_ip,packet.des_mac,packet.des_ip,packet.string);
				}
				else
				{
					printf("\nIP MATCH NOT FOUND");
				}
			
			}
		}
		
	}
	return 0;
}