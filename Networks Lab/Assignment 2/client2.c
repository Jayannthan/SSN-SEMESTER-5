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
    int sockD = socket(AF_INET, SOCK_STREAM, 0); 
    struct sockaddr_in servAddr;
    servAddr.sin_family = AF_INET;
    servAddr.sin_port= htons(port);
    servAddr.sin_addr.s_addr = INADDR_ANY;
    int connectStatus= connect(sockD, (struct sockaddr*)&servAddr,sizeof(servAddr));
    //printf("\nConnected\n");
    if (connectStatus == -1) {
        printf("Error...\n");
    }
    else 
    {
	    int connected=1;
        char fileText[255],filename[100];
        /*while(connected)
    	{*/
    	
		    printf("\nEnter filepath in server:");
		    scanf(" %s",filename);
		    int fd=open(filename,O_RDONLY);
    		read(fd, fileText, sizeof(fileText));
    		printf("\n%s",fileText);
		    int wr=write(sockD,filename,sizeof(filename));
		    printf("\nFilename sent to server\nWaiting for response...\n");
		    recv(sockD, fileText, sizeof(fileText), 0);  
		    printf("Message: %s\n", fileText);
			/*if(strcmp(strData,"exit")==0)
			{
				connected =0;
			}*/
    //	}
    }
    return 0;
}
