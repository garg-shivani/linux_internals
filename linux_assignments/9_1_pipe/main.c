/*
 To understand working of pipe between two process. 

Create two child process and execute commands passed from command-line arguments 
Each command is separated by a '|' (pipe) character. 
First child execute first command (with or without options) and pass o/p to next. 
Second child executes second command (after '|') will reads I/p from first cmd. 
Parent will wait for both child process to finish .
Sample execution: 

./pipe (No arguments)
    Error: No arguments passed Usage: ./pipe   <command1 > '|'   <command2>   

2. ./pipe ls  

    Error: Insufficient arguments passed Usage: ./pipe  <command1 > '|'   <command2>   

3. ./pipe ls '|' wc

    5 25 4. 

4. ./pipe ls ­ -l -­a '|' wc -­l ­-w 

    10 15
*/
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
    if(argc<3)
    {
        printf("Error: No arguments passed Usage: ./pipe <command1> 'l' <command2>\n");
        return 1;
    }
    //find pipe pos
    int pipe_pos = -1;
    for(int i = 1;i<argc;i++)
    {
        if(strcmp(argv[i], "|") == 0){
            pipe_pos = i;
            break;
        }
    }
    if(pipe_pos == 1 || pipe_pos == 1 || pipe_pos == argc -1)
    {
        printf("Error: Improper arguments\nUsage: ./a.out <command1> '|' <command2\n>");
        return 1;
    }
    //split command1 and command2 into arrays
    char* cmd1[MAX_ARGS];
    char* cmd2[MAX_ARGS];
    parse_command(argv, 1, pipe_pos, cmd1);
    parse_command(argv, pipe_pos + 1,argc ,cmd2);
    //create the pipe
    int pipefd[2];
    if(pipe(pipefd) == -1)
    {
        perror("pipe failed\n");
        return 1;
    }
    //create the child1 process
    pid_t c1 = fork();
    if(c1 == 0)
    {
        //modify the FD table to redirect the output to PIPE
        dup2(pipefd[1], 1);
        close(pipefd[0]);
        close(pipefd[1]);
        execvp(cmd1[0], cmd1);
        perror("exec1 failed");
        exit(1);
        //execute the command1 using exec

    }
    pid_t c2 = fork();
    if(c2 == 0)
    {
        //redirect stdin to pipe read end
        dup2(pipefd[0], 0);
        close(pipefd[1]);
        close(pipefd[0]);
        execvp(cmd2[0], cmd2);
        perror("exec2 failed");
        exit(1);
    }
    //parent process
    close(pipefd[0]);
    close(pipefd[1]);
    waitpid(c1, NULL, 0);
    waitpid(c2, NULL, 0);
    return 0;
}