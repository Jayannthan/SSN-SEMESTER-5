#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <sys/socket.h>

int main(int argc, char const *argv[])
{
	if (argc<2)
	{
		printf("Enter port number in terminal\n");
		return 0;
	}

	struct sockaddr_in server;
	server.sin_family=AF_INET;
	server.sin_addr.s_addr=INADDR_ANY;
	server.sin_port=htons(atoi(argv[1]));

	int sockfd=socket(AF_INET,SOCK_STREAM,0);
	bind(sockfd,(struct sockaddr*)&server,sizeof(server));
	listen(sockfd,1);
	int clientsocket=accept(sockfd,NULL,NULL);
	

	char string[] = "101_010_1__";
    int position=0;
    for (int i = 1; i <=11; i++)
    {
        if (i&(i-1))
        {
            continue;
        }
        int parity=0;
        for (int j = i; j <=11; j++)
        {
            if(i&j)
            {
                if(string[11-j]=='1')
                {
                    parity=1-parity;
                }
            }
        }
        char c=parity+'0';
        string[11-i]=c;
    }
    printf("string:%s\n",string);


	
		// read(clientsocket,string,sizeof(string));
		// printf("String:%s",string );

		// printf("Enter string:\n");
		// gets(string);

	write(clientsocket,string,sizeof(string));
	

	return 0;
}