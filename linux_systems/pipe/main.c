/*
It has 2 ends(1 end is read, adm othr end is write)
only 2 process can communicate 
unideirectional lcommunication
one time readable data
size limited(4kb)
acts as serial device
virtual file creted in the kernel space
int pipe(int pipefd[2])
om success = 0
on erro r = -1  
*/
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <string.h>
#include <errno.h>
int main()
{
    int pipefd[2];
    if(pipe(pipefd) == -1)
    {
        perror("pipe");
        exit(-1);
    }
    int ret = fork();
    if(ret >0)
    {
        printf("this is parent process\n");
        close(pipefd[0]);
        write(pipefd[1], "Hello\0", 6);
        printf("writing is successful in the parent\n");
        close(pipefd[1]);
        exit(0);
    }
    else if(ret == 0)
    {
        printf("this is child\n");
        close(pipefd[1]);
        char buf[11];
        read(pipefd[0],buf, 6 );
        printf("After reading the message from pipe is %s\n", buf);
        close(pipefd[0]);
        exit(0); 
        
    }
    else
    {
        perror("fork");
        exit(1);
    }
}


