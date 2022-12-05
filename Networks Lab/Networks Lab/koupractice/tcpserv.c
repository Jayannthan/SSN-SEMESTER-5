#include <netinet/in.h> 
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include<fcntl.h>
int main(){
	char string[]="oombu";
	int sockfd=socket(AF_INET,SOCK_STREAM,0);
	struct sockaddr_in ser;
	ser.sin_family=AF_INET;
	ser.sin_port=8000;
	ser.sin_addr.s_addr=INADDR_ANY;
	bind(sockfd,(struct sockaddr*)&ser,sizeof(ser));
	listen(sockfd,1);
	int clientsocket=accept(sockfd,0,0);
	send(clientsocket,string,sizeof(string),0);

}