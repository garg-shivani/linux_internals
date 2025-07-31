#include "main.h"
//nternal = cd, pwd, jobs, fg, bg
char* internal_cmd[] = {"cd", "pwd", "jobs", "fg", "bg", NULL, "echo"};


int check_command_type(char* user_input)
{
    //logic to check the given command is external or internal/echo
    //extract only command from the inpout
    char input[1024];
    strcpy(input, user_input);

    char *cmd = strtok(input, " ");
    if(strcmp(input, "echo") == 0) return ECHO;

    for(int i =0;internal_cmd[i] != NULL;i++)
    {
        if(strcmp(cmd, internal_cmd[i]) == 0)
        {
            return INTERNAL;
        }
    }
    return EXTERNAL; //if not internal or echo, then it is external command
}