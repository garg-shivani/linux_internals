/*
Description :

Create a scenario to make zombie process become orphan, print status of each state.

Pre-requisites:

Knowledge about system calls, How to read and understand ‘man pages’.
Good knowledge about processes, zombie and orphan.
Working of fork system call.
Objective:

• To understand different states of a process.

Requirements: 

Create a child process and print status that process is running
After some time print status that process is zombie state
After some time print zombie process cleared by init.
To print status use help of /proc//status file.
For eg: if child pid is 1234, open file /proc/1234/status and print first 3 lines
      5. If that file is not available means that process is cleared.
 
Sample execution:
 
1. ./zomb_orph
A child created with pid 1234
Name:  ./zomb_orph
State: S (sleeping)
Name:  /zomb_orph   (After some time)
State: Z (zombie)
Process 1234 cleared by init  (After some time)
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
void print_lines(int fd)
{
    char buffer[1024];
    int n = read(fd, buffer, sizeof(buffer) - 1);
    buffer[n] = '\0';//NUll terminate

    //print first 3 lines
    int line_count = 0;
    char *line = strtok(buffer, "\n");
    while(line != NULL && line_count < 3)
    {
        printf("%s\n", line);
        line = strtok(NULL, "\n");
        line_count++;
    }
}
int main()
{
    int ret;

    pid_t pid = fork();
    if(pid == 0)
    {
    
        //child process
        sleep(2);
    }
    else
    {
        //parent process
        printf("Child created with pid %d\n", pid);
        char path[100];
        sprintf(path,"/proc/%d/status", pid);
        int fd = open(path,O_RDONLY);
        if(fd == -1)
        {
            printf("process is cleared");
        }
        //read 2 lines from the fd
        else
        {
            print_lines(fd);
            close(fd);
        }
        sleep(4);
        //print the status of child
        
        sprintf(path,"/proc/%d/status", pid);
         fd = open(path,O_RDONLY);
        if(fd == -1)
        {
            printf("process is cleared");
        }
        //read 2 lines from the fd
        else
        {
            print_lines(fd);
            close(fd);
        }

        //priting the status of the child
        pid_t pid2 = fork();
        if(pid2 == 0)
        {
            //child2 process
            sleep(2);
            char path[100];
            sprintf(path,"/proc/%d/status", pid);
            int fd = open(path,O_RDONLY);
            if(fd == -1)
            {
                printf("process %d is cleared by init\n",pid );
            }
            //read 2 lines from the fd
            else
            {
                print_lines(fd);
                close(fd);
            }
        }
        else
        {
            //exit(0);
            return 0;
        }
    }
}