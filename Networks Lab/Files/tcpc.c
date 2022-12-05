#include <netinet/in.h> //structure for storing address information
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>

int main(int argc, char const *argv[])
{
	char string[100];
	int sockfd = socket(AF_INET, SOCK_STREAM, 0);
	struct sockaddr_in ser;
	ser.sin_family = AF_INET;
	ser.sin_port = htons(atoi(argv[1]));
	ser.sin_addr.s_addr = INADDR_ANY;
	connect(sockfd, (struct sockaddr *)&ser, sizeof(ser));
	recv(sockfd, string, sizeof(string), 0);
	printf("%s\n", string);
	return 0;
}
