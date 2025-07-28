#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>
/*• To understand, how to avoid zombie asynchronously . 

Requirements: 

 Write two separate programs for both methods.

 Method 1 

1. Create a child process. 
2. Write a signal handler function for SIGCHLD to avoid child become zombie (Do man 7 signal for SIGCHLD) . 
3. Write code inside handler to avoid zombie and print child exit status. 

  Method 2

 1. Create a child process. 
 2. Use sa_flag from struct sigaction to avoid zombie (Refer man ). 
 3. Prints the child exit status inside handler.

Sample execution:  


1. ./avoid_zombie 
child  terminated with exit code 0.*/
//in handler
    //write the program to avoid child become zombie and orint its exit status
void sigchld_handler(int signo)
{
    int status;
    pid_t pid = waitpid(-1, &status, WNOHANG);
    if(pid > 0)
    {
        if(WIFEXITED(status))
        {
            printf("Child %d terminated with exit code %d.\n", pid, WEXITSTATUS(status));

        }
        else
        {
            printf("Child %d terminated abnormally\n", pid);
        }
    }

}   
int main()
{
    //when child terminate or stop it will send SIGCHLD siganl to parent
    //register the SIGCHLD signal using sigaction from the parent 
    //create a child become zombie
    signal(SIGCHLD, sigchld_handler);
    pid_t pid = fork();
    if(pid == 0)
    {
        //child process
        printf("Child process running pid %d...\n", getpid());
        sleep(1);
        exit(0);
    }
    else if(pid > 0)
    {
        //parent process
        printf("Parent process pid %d , child created pid %d\n", getpid(), pid);
        pause();
    }
    else{
        perror("fork");
        exit(1);
    }

    return 0;
}