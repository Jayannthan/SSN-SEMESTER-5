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
	int port=atoi(argv[1]);
    int serSockID = socket(AF_INET, SOCK_STREAM, 0);
    char fileText[255],filename[100];
    struct sockaddr_in servAddr;
    servAddr.sin_family = AF_INET;
    servAddr.sin_port = htons(port);
    servAddr.sin_addr.s_addr = INADDR_ANY;
    bind(serSockID, (struct sockaddr*)&servAddr,sizeof(servAddr));
    listen(serSockID, 1);
    int clientSocket = accept(serSockID, NULL, NULL);
    printf("\nConnected\n");
    int connected=1;
    /*while(connected)
    {*/
    	read(clientSocket,filename,sizeof(filename));
    	int fd=open(filename,O_RDONLY);
    	read(fd, fileText, sizeof(fileText));
    	printf("File Path Recieved: %s\nMessage read:%s\n!!!Sending the file to client!!!\n\n",filename,fileText);
    	send(clientSocket, fileText, sizeof(fileText), 0);
    	/*if(strcmp(serMsg,"exit")==0)
    	{
    		connected =0;
    	}*/
    //}
    return 0;
}

