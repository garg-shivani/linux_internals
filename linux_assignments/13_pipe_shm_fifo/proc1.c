/*Objective: 

To understand how to establish communication between 3 different process using 3 different IPC mechanism.
Requirements: 

Create 2 different process by executing 2 different a.out (executable) file’s
Create a new process (child process) in Process 1
Create a Pipe between Parent and Child Process
Create SHM from any of the process. Either Process 1 or Process 2
In Parent Process 1 
Prompt the user to enter a string 
Write the string in pipe 
Read the string from pipe into child process
Convert the string into Upper case
Write the Upper case string  in shared memory
6.In process 2

 
Read the data from the shared memory 
Reverse input which is read from SHM
Write the Reverse string  in FIFO
7.Read the data from FIFO in Parent process 1
8.Print the output string on stdout*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <ctype.h>
#include <string.h>
#include <fcntl.h>
#define MAX_SIZE 10
#define KEY 0xA
int main()
{
    
    int pipefd[2];
    pipe(pipefd);
    pid_t pid = fork();
    if(pid == 0)
    {
        sleep(5);
        char buf[MAX_SIZE];
        close(pipefd[1]);
        read(pipefd[0], buf,MAX_SIZE );
        printf("After reading  from pipe message is %s\n", buf);
            //convert to uppercase
        for(int i =0;buf[i];i++)
        {
            buf[i] = toupper(buf[i]);
        }
        int shmid = shmget(KEY, 100, IPC_CREAT | 0666);
        if(shmid == -1)
        {
            perror("shmget");
            return -1;
        }
        //attaach the process to shm
        char* ptr = shmat(shmid, NULL, 0);
        if(ptr == (char*)-1)
        {
            perror("shmat");
            return(-1);
        }
        strcpy(ptr, buf);
        printf("upper case string %s send to shared memory\n", ptr);
        close(pipefd[0]);
        shmdt(ptr);
        exit(0);

    }
    else if(pid >  0)
    {
        char buf[MAX_SIZE];
        printf("Enter a string\n");
        close(pipefd[0]);
        fgets(buf, MAX_SIZE, stdin );
        int len = strlen(buf);
        buf[strcspn(buf, "\n")] = '\0';
        write(pipefd[1], buf,len );
        printf("Writing %s in to pipe is success by the parent\n", buf);
        close(pipefd[1]);


        wait(NULL);
        sleep(5);
        int fd = open("my_fifo", O_RDONLY);
        if(fd == -1)
        {
            perror("open ");
            exit(-1);
        }
        char buf1[MAX_SIZE] = {0};

        read(fd, buf1,MAX_SIZE );
        printf("read data from fifo is %s", buf1);
        unlink("my_fifo");
        exit(0);

    }
    else{
        perror("fork");
        exit(1);
    }
    return 0;
}