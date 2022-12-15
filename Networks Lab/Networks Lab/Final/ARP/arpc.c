#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<fcntl.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>

typedef struct ARP
{
	int type;
	char src_ip[20],des_ip[20],src_mac[20],des_mac[20],string[20];
} ARP;

int main(int argc, char const *argv[])
{
	if (argc<2)
	{
		printf("Enter port in terminal\n");
		return 0;
	}
	
	struct sockaddr_in server;
	server.sin_family=AF_INET;
	server.sin_port=htons(atoi(argv[1]));
	server.sin_addr.s_addr=INADDR_ANY;

	int sockfd=socket(AF_INET,SOCK_STREAM,0);
	connect(sockfd,(struct sockaddr*)&server,sizeof(server));

	ARP temp;
	printf("\nEnter Client IP:");
	scanf(" %s",temp.src_ip);
	printf("\nEnter Client MAC:");
	scanf(" %s",temp.src_mac);

	ARP packet;
	read(sockfd,&packet,sizeof(packet));
	if (strcmp(packet.des_ip,temp.src_ip)==0)
	{
		printf("\nIP MATCH\n");
		strcpy(packet.des_mac,temp.src_mac);
		packet.type=1;
		printf("\n\nAcknowledge packet:%d|%s|%s|%s|%s",packet.type,packet.des_mac,packet.des_ip,packet.src_mac,packet.src_ip);
		write(sockfd,&packet,sizeof(packet));
		read(sockfd,&packet,sizeof(packet));
		printf("\n\nFinal packet received with data:%d|%s|%s|%s|%s|%s\n\n",packet.type,packet.src_mac,packet.src_ip,packet.des_mac,packet.des_ip,packet.string);

	}
	else
	{
		printf("\nIP NOT MATCH\n");
		packet.type=2;
		write(sockfd,&packet,sizeof(packet));
	}



	return 0;
}