/*• To understand how to use exec system calls.

Requirements:

Create child and execute a command passed from command-line arguments.  
If no arguments passed print a usage message.
In case any wrong command passed, print an error message.
After child terminates print the exit status of child process.
Sample execution: -
1. No args passed (Print usage info)
./exe_child Usage: ./exe_child args...
2. Valid arg. passed
./exe_child date
This is the CHILD process, with id 11612
Wed Apr  4 13:27:19 IST 2012
Child exited with status 0*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
int main(int argc, char* argv[])
{
    //validat ethe CLA
    //create the child process
    //in parent
        //wait for the child process
        //print the child exit staus
    //in child
        //execute the command using exec
    if(argc <2)
    {
        printf("No args passed(Print usage info)\n./exe_child Usage: ./exe_child args...\n");
        return 1;
    }
    else
    {
        printf("Valid arg. passed\n%s %s\n", argv[0], argv[1]);
        pid_t pid = fork();
        if(pid == 0)
        {
            printf("This is the CHILD process, with id %d\n", getpid());
            execvp(argv[1], &argv[1]);
        }
        else if(pid < 0)
        {
            perror("Fork failed\n");
            return 1;
        }
        else
        {
            //parent process
            int status;
            waitpid(pid, &status, 0);
            if(WIFEXITED(status))
            {
                printf("Child exited with status %d\n", WEXITSTATUS(status));
            }
            else
            {
               printf("Child exited abnormally\n"); 
            }
        }
    }
    return 0;
}