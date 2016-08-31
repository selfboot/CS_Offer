/*
 * @Author: xuezaigds@gmail.com
 * @Last Modified time: 2016-08-28 16:37:05
 */

#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <cstdlib>
#include <cstring>

const int SIZE = 1024;

int main(int argc, char *argv[])
{
    // 创建匿名管道
    if (mkfifo("named_pipe", 0644) == -1){
        printf("Create named pipe failed.\n");
        exit(-1);
    }

    printf("Open named pipe with pending modle...\n");
    int write_fd = open("named_pipe", O_WRONLY);     //打开文件
    if (write_fd == -1){
        printf("Open named pipe failed!\n");
        exit(-1);
    }
    const char *content = "1111222233334444";
    if(write(write_fd, content, strlen(content)) != -1)
    {
        printf("Write data: \n");
        printf("%s\n", content);
    }
    close(write_fd);
    return 0;
}

