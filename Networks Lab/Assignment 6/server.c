#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<fcntl.h>
#include<stdbool.h>
#include<math.h>
#define MAXSIZE 1024

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
int isapower2(int n)
{
    if(ceil(log2(n)) == floor(log2(n)))
    {
        return 1;
    }
    else
    {
        return 0;
    }
}
int main(int argc, char ** argv)
{
    srand(time(NULL));

    if (argc < 2){
        fprintf(stderr, "Enter port number as argument!\n");
        exit(EXIT_FAILURE);
    }

    int PORT = atoi(argv[1]);

    int sockfd, newfd, n, arr[30];
    char buff[MAXSIZE], buffer[MAXSIZE], data_t[40];
    long data;
    struct sockaddr_in servaddr,clientaddr;
    
    if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        perror("Socket creation failed!");
        exit(1);
    }
    
    bzero(&servaddr,sizeof(servaddr));
    servaddr.sin_family = AF_INET; // IPv4
    servaddr.sin_addr.s_addr = INADDR_ANY;
    servaddr.sin_port = htons(PORT);
    
    if(bind(sockfd, (const struct sockaddr *)&servaddr,sizeof(servaddr)) < 0)
    {
        perror("Bind failed!");
        exit(1);
    }
    
    listen(sockfd, 2);
    printf("Enter the data to send: ");
    scanf("%lu", &data);
    long num =data,count = 0;
    while(num > 0)
    {
        num = num / 10;
        count++;
    }
    n=count;
    int r=1;
    //r = log2(n);
    //r = floor(r);
    
    // Finding number of redundant bits
    while(pow(2, r) < n + r + 1)
    {    
    	r += 1;
    }
    
    
    int total = n + r;
    
    printf("\nNo. of redundant bits : %d\nTotal no. of bits:%d\n", r,total);
    //nob = floor(log2(total));
    
    //creating spaces for redundant bits
    for(int i = 1; i <= total; i++)
    {
        int digit = data % 10;
        if(isapower2(i) == 0)
        {
            arr[total - i] = digit;
            data /= 10;
        }
        else
        {
            arr[total-i]=0;
        }
    }
    
    //assigning redundant bits
    for(int i = 0; i < r; i++)
    {
        for(int j = 1; j <= total; j++)
        {
            if((int)(pow(2, i)) != j)
            {
                int bin = binary(j);
                if(ispresent(bin, i + 1))
                    count += arr[total - j];
            }
        }
        if(count % 2 == 0)
            arr[total - (int)(pow(2, i))] = 0;
        else
            arr[total - (int)(pow(2, i))] = 1;
        count = 0;
    }
    
    
    printf("\nData with redundant bits: ");
    for(int i = 0; i < total; i++)
    {
        printf("%d", arr[i]);
    }
    // printf("\nEnter error position: ");
    // scanf("%d", &pos);

    int pos = rand() % total + 1;
    printf("\nIntroducing error randomly at bit: %d\n", pos);

    if(arr[total - pos] == 0)
    {
        arr[total - pos] = 1;
    }
    else
    {
        arr[total - pos] = 0;
    }
    
    int k = 0;
    num = 0;
    for(int i = total - 1; i >= 0; i--)
    {
        num += pow(10, k) * arr[i];
        k++;
    }
    sprintf(data_t, "%lu", num);
    printf("Data transmitted is %s\n", data_t);
    int len = sizeof(clientaddr);
    newfd = accept(sockfd, (struct sockaddr*)&clientaddr, &len);
    int m = write(newfd, data_t, sizeof(data_t));
}
