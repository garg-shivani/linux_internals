#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <stdlib.h>
int main()
{
    pid_t pid = fork();
    if(pid == 0)
    {
        //child
      
        sleep(10);
    }
    else if(pid >0)
    {
        int status;
        int flag = 1;
        printf("A child created with pid %d\n", pid);
        for(int i =0;i<15;i++)
        {
            
            waitpid(pid, &status, WNOHANG);
            if(WIFEXITED(status) && flag)
            {
                printf("Child %d terminated normally with exit status %d parent treminating\n",pid, WEXITSTATUS(status));
                flag = 0;
            }
            printf("Parent is running\n");
            sleep(1);
        }
    }
    else
    {
        perror("fork");
        exit(1);
    }
    return 0;
}