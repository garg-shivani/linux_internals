#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#define MAX_ARGS 100
#define MAX_CMDS 50
//parse argcv into individual commnd arrays, splitting on '|'
int parse_commands(char *argv[], int argc, char *cmds[][MAX_ARGS])
{
    int cmd_index = 0, arg_index = 0;
    for(int i = 1; i <argc; i++)
    {
        if(strcmp(argv[i] , "|") == 0){
            cmds[cmd_index][arg_index] = NULL;
            cmd_index++;
            arg_index = 0;
        }
        else
        {
            cmds[cmd_index][arg_index++] = argv[i];
        }
    }
    cmds[cmd_index][arg_index] = NULL;
    return cmd_index + 1;// total nuber of commands
}
int main(int argc, char*argv[])
{
    if(argc< 4)
    {
        printf("Usage: ./pipe <cmd1> '|' <cmd2> .. '|' <cmdN>\n");
        return 1;
    }
    char* cmds[MAX_CMDS][MAX_ARGS];
    int num_cmds = parse_commands(argv, argc, cmds);
    int num_pipes = num_cmds - 1;
    int pipes[num_pipes][2];
    //create all pipes
    for(int i =0;i<num_pipes;i++)
    {
        if(pipe(pipes[i]) == -1)
        {
            perror("pipe");
            exit(1);
        }
    }
    //create child processes for each command
    for(int i =0;i<num_cmds;i++)
    {
        pid_t pid = fork();
        if(pid == 0)
        {
            //if not the first commd, read from previpsu pipe
            if(i >0)
            {
                dup2(pipes[i -1][0], 0);
            }
            //if not the last commnd, write to next pipe
            if(i < num_cmds - 1)
            {
                dup2(pipes[i][1], 1);
            }
            //close all pipe ends in child
            for(int j = 0;j<num_pipes;j++)
            {
                close(pipes[j][0]);
                close(pipes[j][1]);
            }
            execvp(cmds[i][0], cmds[i]);
            perror("exec failed");
            exit(1);

        }
    }
    //parent closes all pipes ends
    for(int i = 0;i<num_pipes;i++)
    {
        close(pipes[i][0]);
        close(pipes[i][1]);
    }
    //wait for all children
    for(int i = 0;i<num_cmds;i++)
    {
        wait(NULL);
    }
    return 0;
}