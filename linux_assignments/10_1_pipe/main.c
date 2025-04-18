/*Pre-requisites:- 

Knowledge about system calls, How to read and understand ‘man pages’.
Good knowledge about processes and IPC. 
Working of pipe & dup system calls.
Objective: 

• To understand working of pipe between two process. 

Requirements: 

Create three child process and execute commands passed from command-line arguments 
Each command is separated by a '|' (pipe) character. 
First child execute first command (with or without options) and pass o/p to next. 
Second child executes second command (after '|') will reads I/p from first pipe. 
Third Child execute third command (after 2nd pipe '|') will read i/p from second pipe.
Parent will wait for  child process to finish .
Sample execution:

 ./three_pipes (No arguments)
 Error: No arguments passed Usage: ./three_pipes  <command1 > '|'   <command2> '|'  <command3 >       

2. ./pipe ls ­l '|' grep 

 Error: Insufficient arguments passed Usage: ./pipe  <command1 > '|'   <command2> '|'  <command3 >

3. ./pipe ls -­l '|' grep “pattern” '|' wc -­l 

5 5 25*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#define MAX_ARGS 100
void parse_command(char* argv[], int start, int end, char* cmd[])
{
    int j = 0;
    for(int i = start;i<end;i++)
    {
        cmd[j++] = argv[i];
    }
    cmd[j] = NULL;
}
int main(int argc, char*argv[])
{
    //do validation of cla 
    if(argc<6)
    {
        printf("Error: Insufficient arguments passed Usage: ./pipe <command1> '|' <command2> '|' <command3>\n");
        return 0;
    }
    //find pipe pos
    int pipe_pos[2] = {-1,-1};
    int j = 0;
    for(int i = 1;i<argc;i++)
    {
        if(strcmp(argv[i], "|") == 0){
            if(j <2)
            {
                pipe_pos[j++] = i;
            }
        }
    }
    if(pipe_pos[0]  == -1 || pipe_pos[1] == -1 || pipe_pos[0]  ==  1 || pipe_pos[1] == (argc -1))
    {
        printf("Error: Improper arguments\n /pipe <command1> '|' <command2> '|' <command3>\n");
        return 1;
    }
    //split command1 and command2  and command3 into arrays
    char* cmd1[MAX_ARGS];
    char* cmd2[MAX_ARGS];
    char* cmd3[MAX_ARGS];
    parse_command(argv, 1, pipe_pos[0], cmd1);
    parse_command(argv, pipe_pos[0] + 1, pipe_pos[1] ,cmd2);
    parse_command(argv, pipe_pos[1] + 1, argc ,cmd3);
    //create the pipe
    int pipefd1[2];
    int pipefd2[2];
    if(pipe(pipefd1) == -1 || pipe(pipefd2) == -1)
    {
        perror("pipe failed\n");
        exit(1);
    }
    //create the child1 process
    pid_t c1 = fork();
    if(c1 == 0)
    {
        //modify the FD table to redirect the output to PIPE
        dup2(pipefd1[1], 1);
        close(pipefd1[0]);
        close(pipefd1[1]);
        close(pipefd2[1]);
        close(pipefd2[0]);
        execvp(cmd1[0], cmd1);
        perror("exec1 failed");
        exit(1);
        //execute the command1 using exec

    }
    pid_t c2 = fork();
    if(c2 == 0)
    {
        //redirect stdin to pipe read end
        dup2(pipefd1[0], 0);
        dup2(pipefd2[1], 1);
        close(pipefd1[1]);
        close(pipefd1[0]);
        close(pipefd2[1]);
        close(pipefd2[0]);
        execvp(cmd2[0], cmd2);
        perror("exec2 failed");
        exit(1);
    }
    pid_t c3 = fork();
    if(c3 == 0)
    {
        //modify the FD table to redirect the output to PIPE
        dup2(pipefd2[0],0);
        close(pipefd1[1]);
        close(pipefd1[0]);
        close(pipefd2[1]);
        close(pipefd2[0]);
        execvp(cmd3[0], cmd3);
        perror("exec3 failed");
        exit(1);
        //execute the command1 using exec
    }
    //parent process
    close(pipefd1[0]);
    close(pipefd1[1]);
    close(pipefd2[0]);
    close(pipefd2[1]);
 

    waitpid(c1, NULL, 0);
    waitpid(c2, NULL, 0);
    waitpid(c3, NULL, 0);


    return 0;
}