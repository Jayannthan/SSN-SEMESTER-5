#include <netinet/in.h> 
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include<fcntl.h>
int main(){
	char string[100]; 
	int sockfd=socket(AF_INET,SOCK_STREAM,0);
	struct sockaddr_in serv;
	serv.sin_family=AF_INET;
	serv.sin_port=8000;
	serv.sin_addr.s_addr=INADDR_ANY;
	connect(sockfd,(struct sockaddr*)&serv,sizeof(serv));
	recv(sockfd,string,sizeof(string),0);
	printf("%s\n",string);
}