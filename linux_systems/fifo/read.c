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
   
    //open the file in write only mode
    int fd = open("myfifo", O_RDONLY);
    if(fd == -1)
    {
        perror("open ");
        exit(-1);
    }
    char buf[12];
    read(fd, buf, 6);
    printf("%s\n", buf);
    close(fd);
}