/*
 * @Author: xuezaigds@gmail.com
 * @Last Modified time: 2016-08-28 16:42:20
 */

#include <stdio.h>
#include <fcntl.h>
#include <cstdlib>
#include <unistd.h>
const int SIZE = 4;

int main(int argc, char *argv[])
{
    // 只读模式打开命名管道
    int read_fd = open("named_pipe", O_RDONLY);
    if (read_fd == -1){
        printf("Open fifo error!\n");
        exit(-1);
    }

    char buf[SIZE];
    int readBytes;
    printf("Read data as follows: \n");
    while ((readBytes = read(read_fd, buf, sizeof(buf))) > 0)
    {
        printf("%s\n", buf);
    }

    unlink("named_pipe");   //删除FIFO
    return 0;
}
