#include "main.h"
#define MAX_ARGS 100
int execute_external_command(char* input)
{
    char *cmd[MAX_ARGS];
    int i =0, exit_val;
    //tokenize inut into cmd[]
    char* token = strtok(input, " \t\n");
    while(token != NULL && i< MAX_ARGS -1)
    {
        cmd[i++] = token;
        token = strtok(NULL, "\t\n");
    }
    cmd[i] = NULL;
    if(cmd[0] == NULL)
    {
        return;//no command entered
    }
    pid_t ret = fork();
    if (ret == 0)
    {
        //child process
        //execute the given command
        //to do conert array of characers into array of NULL terminated strings
        execvp(cmd[0], cmd);
        exit(errno);
    }
    else if(ret >0)
    {
        int status;
        if(waitpid(ret, &status, WUNTRACED) == -1)
        {
            perror("Wait pid");
            return FAILURE;
        }
        if(WIFEXITED(status))
        {
            printf("Child terminating with value %d\n", ret,(exit_val = WEXITSTATUS(status)));
        }
        else if(WIFSIGNALED(status))
        {
            printf("Child terminated abnormally by receiving signal %d\n", (exit_val =WTERMSIG(status)));
        }
        else if(WIFSTOPPED(status))
        {
            printf("Child %d stopped by receiving signal %d\n",(exit_val = WSTOPSIG(status)));
        }
        return exit_val +=128;
        
    }
    else
    {
        perror("fork failed");
    }

}