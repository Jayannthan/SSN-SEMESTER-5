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
	if (argc<3)
	{
		printf("Enter 2 port numbers in terminal\n");
		return 0;
	}

	struct sockaddr_in server1;
	server1.sin_family=AF_INET;
	server1.sin_addr.s_addr=INADDR_ANY;
	server1.sin_port=htons(atoi(argv[1]));

	int sockfd=socket(AF_INET,SOCK_STREAM,0);
	bind(sockfd,(struct sockaddr*)&server1,sizeof(server1));
	listen(sockfd,1);
	int clientsocket1=accept(sockfd,NULL,NULL);


	struct sockaddr_in server2;
	server2.sin_family=AF_INET;
	server2.sin_addr.s_addr=INADDR_ANY;
	server2.sin_port=htons(atoi(argv[2]));

	sockfd=socket(AF_INET,SOCK_STREAM,0);
	bind(sockfd,(struct sockaddr*)&server2,sizeof(server2));
	listen(sockfd,1);
	int clientsocket2=accept(sockfd,NULL,NULL);
	while(1)
	{
		//get roll no. from client1
		int roll;
		read(clientsocket1,&roll,sizeof(roll));
		printf("Roll no:%d\n\n",roll);


		//sends roll to client2
		write(clientsocket2,&roll,sizeof(roll));



		int marks[5];
		float average=0.0f;
		//gets marks for 5 subjects
		for (int i = 0; i < 5; ++i)
		{
			read(clientsocket2,&marks[i],sizeof(marks[i]));
			printf("Mark[%d]:%d\n",i+1,marks[i]);
			average+=marks[i];
		}
		average=average/5;
		printf("Average=%.2f\n",average);

		write(clientsocket1,&average,sizeof(average));

	}
	
	return 0;
}