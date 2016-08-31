/*
 * @Author: xuezaigds@gmail.com
 * @Last Modified time: 2016-08-28 11:11:10
 */

#include <unistd.h>
#include <stdio.h>
#include <cstring>
#include <cstdlib>

int main()
{
    int pipe_fd[2];
    pid_t pid;

    char r_buf[4];
    char w_buf[100];
    memset(r_buf,0,sizeof(r_buf));
    memset(w_buf,0,sizeof(w_buf));
    int r_num;

    if(pipe(pipe_fd)<0)
    {
        printf("pipe create error\n");
        return -1;
    }

    if((pid=fork())==0)     // 子进程
    {
        printf("\n");
        close(pipe_fd[1]);  // 关闭写端
        sleep(5);           // 确保父进程关闭写端
        while((r_num=read(pipe_fd[0],r_buf,4))!=0)
            printf( "Read data from the pipe is %s\n", r_buf);

        close(pipe_fd[0]);  // 关闭读端
        exit(0);
    }
    else if(pid>0)          // 父进程
    {
        close(pipe_fd[0]);  // 关闭读端
        const char* content = "1111222233334444";
        strncpy(w_buf, content, strlen(content));
        if(write(pipe_fd[1],w_buf, strlen(content))!=-1){
            printf("Write data %s\n", w_buf);
            printf("Parent write over\n");
        }
        close(pipe_fd[1]);  // 关闭写端
        printf("parent close fd[1] over\n");
        wait(&pid);         // 等待子进程结果
    }
}
