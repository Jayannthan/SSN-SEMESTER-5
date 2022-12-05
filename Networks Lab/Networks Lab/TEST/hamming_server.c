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
    int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    struct sockaddr_in ser;
    ser.sin_family = AF_INET;
    ser.sin_port = htons(atoi(argv[1]));
    ser.sin_addr.s_addr = INADDR_ANY;

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
    string[6]='1';
    strcpy(string,"10100111110");
    printf("string:%s\n",string);

    
    sendto(sockfd, string, sizeof(string), MSG_CONFIRM, (struct sockaddr*)&ser, sizeof(ser));
    printf("MSG SENT\n");    
    return 0;
}
