#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <ctype.h>
#include <string.h>
#include <fcntl.h>
#include <errno.h>
#define KEY 0xA
void reverse_str(char * str)
{
    int len = strlen(str);
    for(int i =0;i<len/2;i++)
    {
        char temp;
        temp = str[i];
        str[i] = str[len - 1-i];
        str[len - 1-i] = temp;
    }
}
int main()
{
    int shmid = shmget(KEY, 100, 0);
    if(shmid == -1)
    {
        perror("shmget failed");
        exit(1);
    }
    //atatch the process
    char* ptr = (char*)shmat(shmid, NULL, 0);
    if(ptr == (char*)-1)
    {
        perror("shmat failed");
        exit(1);
    }
    if (strlen(ptr) == 0) {
        printf("Shared memory seems empty!\n");
        return 0;
    }
    printf("Process 2 received string %s\n", ptr);
    reverse_str(ptr);
    umask(0);
    if(mkfifo("my_fifo", 0666) == -1)
    {
        if(errno != EEXIST)
        {
            perror("mkfifo");
            exit(-1);
        }
    }
    //open the file in write only mode
    int fd = open("my_fifo", O_WRONLY);
    if(fd == -1)
    {
        perror("open ");
        exit(-1);
    }
    write(fd, ptr, strlen(ptr));
    printf("write to fifo is success\n");
    shmdt(ptr);
    shmctl(shmid, IPC_RMID, NULL);
    return 0;
}