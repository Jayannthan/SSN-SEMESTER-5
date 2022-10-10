#include<stdio.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<string.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<stdlib.h>
#include<math.h>
#define MAXLINE 1024

int countbits(long num)
{
    int r, count = 0;
    while(num > 0)
    {
        num = num / 10;
        count++;
    }
    return count;
}

int binary(int num)
{
    int bin = 0, r;
    int i = 0;
    while(num > 0)
    {
        r = num % 2;
        bin += r * pow(10, i);
        num /= 2;
        i++;
    }
    return bin;
}

int ispresent(int num,int pos)
{
    int rem;
    for(int i = 0; i < pos; i++)
    {
        rem = num % 10;
        num = num / 10;
    }
    if(rem == 1)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int decimal(int num)
{
    int rem, i = 0, result;
    while(num > 0)
    {
        rem = num % 10;
        result += pow(2, i) * rem;
        num /= 10;
        i++;
    }
    return result;
}


int main(int argc, char **argv)
{
    if (argc < 2){
        fprintf(stderr, "Please enter port number as second argument!\n");
        exit(EXIT_FAILURE);
    }

    int PORT = atoi(argv[1]);

    long num;
    int sockfd, arr[20], newarr[20], finalarr[20];
    char buffer1[40];int binary(int num)
{
    int bin = 0, r;
    int i = 0;
    while(num > 0)
    {
        r = num % 2;
        bin += r * pow(10, i);
        num /= 2;
        i++;
    }
    return bin;
}
    struct sockaddr_in servaddr;
    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("Socket creation failed!");
        exit(1);
    }
    bzero(&servaddr,sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(PORT);
    servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    int n, len;
    connect(sockfd, (struct sockaddr*)&servaddr, sizeof(servaddr));
    n = read(sockfd, buffer1, sizeof(buffer1));
    num = atol(buffer1);
    
    
    int count = 0;
    long num1=num;
    while(num1 > 0)
    {
        num1 = num1 / 10;
        count++;
    }
    int total = count;
    
    
    printf("Received data: %lu\nTotal bits:%d\n", num,total);
    
    
    int i = 1;
    while(num > 0)
    {
        int rem = num % 10;
        arr[total - i] = rem;
        num /= 10;
        i++;
    }
    
    
    //calculationg number of redundant bits
    int r=0;
    for(i = 1; i <= total; i++)
    {
        if(ceil(log2(i)) == floor(log2(i)))
        {
            r++;
        }
    }
    
    //checking parity of redundant bits
    int result=0,k = 0;
    for(i = 0; i < 4; i++)
    {
        for(int j = 1; j <= total; j++)
        {
            int bin = binary(j);
            if(ispresent(bin, i + 1))
            {
                count += arr[total - j];
            }
        }
        if(count % 2 == 0)
        {
            result += pow(10, k) * 0;
        }
        else
        {
            result += pow(10, k) * 1;
        }
        k++;
        count=0;
    }
    
    
    int error = decimal(result);
    printf("\nError bit in binary: %d\n", result);
    printf("\nError in bit in decimal %d\n", error);
    
    //error correction at error bit
    if(arr[total - error] == 0)
    {
        arr[total - error] = 1;
    }
    else
    {
        arr[total - error] = 0;
    }
    
    
    printf("\nMessage after error correction: ");
    for(i = 0; i < total; i++)
    {
        printf("%d", arr[i]);
    }
    printf("\n");
    
    
    //shifting bits to its position
    k = 0;
    for(i = total - 1; i >= 0; i--)
    {
        newarr[k] = arr[i];
        k++;
        
    }
    
    //removing redundant bits
    int x = 0;
    for(i = 0;i < k; i++)
    {
        if(ceil(log2(i + 1)) != floor(log2(i + 1)))
        {
            finalarr[x] = newarr[i];
            x++;
        }
    }
    
    printf("\nData after error correction and removing redundant bits: ");
    for(i = x - 1; i >= 0; i--)
        printf("%d", finalarr[i]);
    printf("\n");
    return 0;
}
