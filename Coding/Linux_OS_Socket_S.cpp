/*
 * @Last Modified time: 2016-09-01 10:15:52
 */

#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>

int main()
{
    int server_sockfd = -1;
    int client_sockfd = -1;
    int client_len = 0;
    struct sockaddr_in server_addr;
    struct sockaddr_in client_addr;
    //创建流套接字
    server_sockfd = socket(AF_INET, SOCK_STREAM, 0);
    //设置服务器接收的连接地址和监听的端口
    server_addr.sin_family = AF_INET;//指定网络套接字
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);//接受所有IP地址的连接
    server_addr.sin_port = htons(9736);//绑定到9736端口
    //绑定（命名）套接字
    bind(server_sockfd, (struct sockaddr*)&server_addr, sizeof(server_addr));
    //创建套接字队列，监听套接字
    listen(server_sockfd, 5);
    //忽略子进程停止或退出信号
    signal(SIGCHLD, SIG_IGN);

    while(1)
    {
        char ch = '\0';
        client_len = sizeof(client_addr);
        printf("Server waiting\n");
        //接受连接，创建新的套接字
        client_sockfd = accept(server_sockfd, (struct sockaddr*)&client_addr,
                               (socklen_t *)&client_len);

        if(fork() == 0)
        {
            //子进程中，读取客户端发过来的信息，处理信息，再发送给客户端
            read(client_sockfd, &ch, 1);
            sleep(5);
            ch++;
            write(client_sockfd, &ch, 1);
            close(client_sockfd);
            exit(0);
        }
        else
        {
            //父进程中，关闭套接字
            close(client_sockfd);
        }
    }
}

