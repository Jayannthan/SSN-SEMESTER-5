#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
  
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
        char strData[255];
        while(connected)
    	{
    	
		    printf("\nEnter data to send to server:");
		    scanf(" %[^\n]s",strData);
		    write(sockD,strData,sizeof(strData));
		    recv(sockD, strData, sizeof(strData), 0);  
		    printf("Message: %s\n", strData);
			if(strcmp(strData,"exit")==0)
			{
				connected =0;
			}
    	}
    }
    return 0;
}

