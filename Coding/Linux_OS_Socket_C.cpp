/*
 * @Author: xuezaigds@gmail.com
 * @Last Modified time: 2016-09-01 10:17:08
 */

#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>

int main()
{
    int sockfd = -1;
    int len = 0;
    struct sockaddr_in address;
    int result;
    char ch = 'A';
    //创建流套接字
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    //设置要连接的服务器的信息
    address.sin_family = AF_INET;//使用网络套接字
    address.sin_addr.s_addr = inet_addr("127.0.0.1");//服务器地址
    address.sin_port = htons(9736);//服务器所监听的端口
    len = sizeof(address);
    //连接到服务器
    result = connect(sockfd, (struct sockaddr*)&address, len);

    if(result == -1)
    {
        perror("ops:client\n");
        exit(1);
    }
    //发送请求给服务器
    write(sockfd, &ch, 1);
    //从服务器获取数据
    read(sockfd, &ch, 1);
    printf("char form server = %c\n", ch);
    close(sockfd);
    exit(0);
}

