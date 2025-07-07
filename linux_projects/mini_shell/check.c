#include "main.h"
//nternal = cd, pwd, jobs, fg, bg
char* internal_cmd[] = {"cd", "pwd", "jobs", "fg", "bg", NULL};
char* getword(char* input)
{
    char* word = strtok(input, " \t\n");
    return word;
}

int check_command_type(char* input)
{
    //logic to check the given command is external or internal/echo
    //extract only command from the inpout
    char *cmd = getword(input);
    
    for(int i =0;internal_cmd[i] != NULL;i++)
    {
        if(strcmp(cmd, internal_cmd[i]) == 0)
        {
            return INTERNAL;
        }
        else if(strcmp(cmd, "echo") == 0)
        {
            return ECHO;
        }
    }
    return EXTERNAL;
}