#include <netinet/in.h> //structure for storing address information
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include<fcntl.h>

int main(int argc, char const* argv[])
{
	char string[] = "Hello World";
	int sockfd = socket(AF_INET, SOCK_STREAM, 0);
	struct sockaddr_in ser;
	ser.sin_family = AF_INET;
	ser.sin_port = htons(atoi(argv[1]));
	ser.sin_addr.s_addr = INADDR_ANY;
	bind(sockfd, (struct sockaddr*)&ser, sizeof(ser));
	listen(sockfd, 1);
	int clientsocket = accept(sockfd, NULL, NULL);
	send(clientsocket, string, sizeof(string), 0);
	return 0;
}
