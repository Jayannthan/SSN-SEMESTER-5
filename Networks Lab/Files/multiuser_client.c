#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define PORT 3230

int main(int argc, char* argv[]) {

	int clientSocket, ret;
	struct sockaddr_in serverAddr;


	clientSocket = socket(AF_INET, SOCK_STREAM, 0);
	if (clientSocket < 0) {
		printf("Error in connection.\n");
		exit(1);
	}

	memset(&serverAddr, '\0', sizeof(serverAddr));
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(PORT);
	serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");

	ret = connect(clientSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr));
	if (ret < 0) {
		printf("Error in connection.\n");
		exit(1);
	}

	while (1) {
		char buffer[1024];
		printf("%s: \t", argv[1]);
		fgets(buffer, 1024, stdin);
		send(clientSocket, buffer, sizeof(buffer), 0);

		if (strcmp(buffer, ":exit") == 0) {
			close(clientSocket);
			printf("Disconnected from server.\n");
			exit(1);
		}

		if (recv(clientSocket, buffer, 1024, 0) < 0) {
			printf("[-]Error in receiving data.\n");
		}
		else {
			printf("Server: \t%s\n", buffer);
		}
	}

	return 0;
}

