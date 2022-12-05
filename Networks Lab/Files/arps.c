#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <netinet/in.h>
#include <sys/socket.h>

#include "arpheader.h"

int main(int argc, char **argv) {

	if (argc < 2) {
		fprintf(stderr, "Enter port number as second argument!\n");
		exit(EXIT_FAILURE);
	}

	int PORT = atoi(argv[1]);

	struct sockaddr_in server, client;
	char buffer[1024];
	int client_sockets[10] = {0}, max, fd, sockfd, newfd, activity;
	int k, i, len, count;
	fd_set newfds;

	arp packet, recv_packet;

	packet = createARPPacket(REQ);
	printf("\nDeveloping ARP Request packet\n");
	printPacket(packet);
	printf("\tThe ARP Request packet is broacasted.\n");
	printf("Waiting for ARP Reply...\n");

	sockfd = socket(AF_INET, SOCK_STREAM, 0);

	if (sockfd < 0) {
		perror("Unable to open socket.\n");
		exit(EXIT_FAILURE);
	}

	bzero(&server, sizeof(server));

	server.sin_family = AF_INET;
	server.sin_addr.s_addr = INADDR_ANY;
	server.sin_port = htons(PORT);

	if (bind(sockfd, (struct sockaddr*)&server, sizeof(server)) < 0) {
		perror("Bind error occurred.\n");
		exit(EXIT_FAILURE);
	}

	listen(sockfd, 10);

	len = sizeof(client);

	while (1) {

		newfd = accept(sockfd, (struct sockaddr*)&client, &len);
		send(newfd, (void*)&packet, sizeof(packet), 0);
		for (i = 0; i < 10; i++)
		{
			if (client_sockets[i] == 0)
			{
				client_sockets[i] = newfd;
				break;
			}
		}

		for (i = 0; i < 10; i++) {
			fd = client_sockets[i];
			// bzero((void*)&recv_packet, sizeof(recv_packet));


			recv(fd, (void*)&recv_packet, sizeof(recv_packet), 0);

			// Check ARP response
			if (recv_packet.mode == ACK) {
				printf("\nARP Reply received: \n");
				printPacket(recv_packet);

				strcpy(packet.dest_mac, recv_packet.src_mac);
				packet.mode = DATA;

				printf("\nSending the packet to: %s\n", packet.dest_mac);

				send(newfd, (void*)&packet, sizeof(packet), 0);
				printf("Packet sent: \n");
				printPacket(packet);
				exit(EXIT_SUCCESS);
			}

		}

	}
	close(sockfd);
	return 0;
}
