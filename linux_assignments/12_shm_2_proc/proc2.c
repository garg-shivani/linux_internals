#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <string.h>
#include <ctype.h>
#include <sys/shm.h>


#define KEY 0xA
void reverse_string(char* str)
{
    int len  = strlen(str);
    for(int i =0;i<len/2;i++)
    {
        char tmp = str[i];
        str[i] = str[len - 1- i];
        str[len - 1- i]  = tmp;
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
    //attch
    char* ptr = (char*)shmat(shmid, NULL, 0);
    if(ptr == (char*)-1)
    {
        perror("shmat failed");
        exit(1);
    }
    //read string from share dmemory
    printf("Process 2 received string %s\n", ptr);
    //reve the string
    reverse_string(ptr);
    //send string to proc1
    printf("Process 2 revered strig and wrote back %s\n", ptr);
    //detatch 
    shmdt(ptr);
    return 0;
}
    