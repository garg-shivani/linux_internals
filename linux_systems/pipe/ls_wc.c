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
       dup2(pipefd[1], 1);
       execlp("ls", "ls", NULL);
        
    }
    else if(ret == 0)
    {
        printf("this is child\n");
        close(pipefd[1]);
        dup2(pipefd[0], 0);
        execlp("wc", "wc", NULL);
    
    }
    else
    {
        perror("fork");
        exit(1);
    }
}


