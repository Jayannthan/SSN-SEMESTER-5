#include <netinet/in.h> 
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <string.h>
#include <sys/types.h>
  
int main(int argc, char const* argv[])
{
	int port=atoi(argv[1]);
    int serSockID = socket(AF_INET, SOCK_STREAM, 0);
    char serMsg[255] = "Hello Client";
    struct sockaddr_in servAddr;
    servAddr.sin_family = AF_INET;
    servAddr.sin_port = htons(port);
    servAddr.sin_addr.s_addr = INADDR_ANY;
    bind(serSockID, (struct sockaddr*)&servAddr,sizeof(servAddr));
    listen(serSockID, 1);
    int clientSocket = accept(serSockID, NULL, NULL);
    printf("\nConnected\n");
    int connected=1;
    while(connected)
    {
    	read(clientSocket,serMsg,sizeof(serMsg));
    	printf("Message recieved: %s\n!!!Sending message again to client!!!\n\n",serMsg);
    	send(clientSocket, serMsg, sizeof(serMsg), 0);
    	if(strcmp(serMsg,"exit")==0)
    	{
    		connected =0;
    	}
    }
    return 0;
}

