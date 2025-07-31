#include "main.h"
#define MAX_ARGS 100
int ext_val;
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

execute_internal_command(char* input)
{
    //1. cd 2. exit 3. pwd 4. jobs 5. fg 6. bg
    //cd == int chdir(const char *path)
    //pwd==> char* get_current_dir_name(void);
    //jobs ==> Display pending processes with teh status
    //fg ==> Resume the recently stopped prpcess in the foreground
    //bg ==> Resume the recently stopped process in the background
  char* command = strtok(input, " \n");
  if(!strcmp(command, "cd")
  {
    char* path = strtok(NULL, " \n");
    if(path == NULL) path = getenv("HOME");
    if(chdir(path) != 0) perror("cd failed");
  }
  else   if(!strcmp(command, "pwd")
  {
    char cwd[1024];
    if(getcwd(cwd, sizeof(cwd)) != NULL)
      printf("%s\n", cwd);
    else
      perror("pwd failed");
  }
  else   if(!strcmp(command, "jobs")
  {
    
  }
  else   if(!strcmp(command, "fg")
  {}
  else   if(!strcmp(command, "bg")
  {}
}

void echo(char* input)
{
    //input :\echo $$
    /*display the pid of mini shell (getpid())*/
    //inout $? --> print teh return value of previosu program
    //$SHELL ->print the nameof teh minshell (get_current_dir_name())
    //echo with nay string --> print that string

    if(strcmp(input, "$$") == 0)
    {
        printf("%d\n", getpid());
    }
    else if(strcmp(input, "$?") == 0)
    {
        printf("%d\n", ext_val);
    }
    else if(strcmp(input, "$SHELL") == 0)
    {
        char directory_name[100]; 
        getcwd(directory_name,100);
        printf("%s\n", directory_name);
    }
    else
    {
        printf("%s\n", input);
    }
}