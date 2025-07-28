//It is nothing but called as Named piipe
//by using this FIFO, we can communicate between two unrelated processes
//It is not a virtual file  
//fifo creation
// mkfifo (command /library fucntion)
//
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <string.h>
#include <errno.h>
int main()
{
    umask(0);
    if(mkfifo("myfifo", 0666) == -1)
    {
        if(errno != EEXIST)
        {
            perror("mkfifo");
            exit(-1);
        }
    }
    //open the file in write only mode
    int fd = open("myfifo", O_WRONLY);
    if(fd == -1)
    {
        perror("open ");
        exit(-1);
    }
    write(fd, "Hello\0", 6);
    printf("write operation successfully\n");
    close(fd);
    exit(0);
}