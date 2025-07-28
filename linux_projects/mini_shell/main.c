/*
Implement a mini shell by using th esystem calls 
using some minimal requirement
Description:

Implement a minimalistic shell, mini-shell(msh) as part of the Linux Internal module.

Objective:

 

The objective is to understand and use the system calls w.r.t process creation, signal handling, process synchronization, exit status, text parsing etc..

 

Requirement details:

1.Provide a prompt for the user to enter commands

1. Display the default prompt as msh>
2. Prompt should be customizable using environmental variable PS1
 • To change the prompt user will do PS1=NEW_PROMPT
 • Make sure that you do not allow whitespaces between = i.e., do not allow PS1 = NEW_PROMPT
• In the above case, it should be treated like a normal command
 
2. Execute the command entered by the user

1. User will enter a command to execute
2. If it is an external command
 • Create a child process and execute the command
• Parent should wait for the child to complete
 • Only on completion, msh prompt should be displayed
 • If user entering without a command should show the prompt again
 
3 Special Variables:

1. Exit status of the last command (echo $?)
 • After executing a command the exit status should be available
 • echo $? should print the exit status of the last command executed
2. PID of msh (echo $$)
• echo $$: should print msh's PID
3. Shell name (echo $SHELL)
• echo $SHELL: should print msh executable path

 4 Signal handling

Provide shortcuts to send signals to running program
1. Ctrl-C (Send SIGINT)
     On pressing Ctrl-C
• If a programming is running in foreground, send SIGINT to the program (child process)
• If no foreground program exists, re-display the msh prompt 2. Ctrl+z (Send SIGSTP)
2. Ctrl-z (Send SIGTSTP)
      On pressing Ctrl+z
• The program running in foreground, should stop the program and parent will display pid of child 2.5

5.Built-in commands

1. exit exit: This command will terminate the msh program
2. cd cd: Change directory
3. pwd: show the current working directory

6 Background Process / Job control

1. Allow a program to run in background To run a program in background use ampersand (&) after the command. For eg: sleep 50 &
2. Implement fg, bg and jobs commands
• bg will will move a stopped process to background sleep 10 & is equallent to sleep 10 then ctrl + z and bg
After this the msh prompt should be displayed indicating it is readyto accept further commands. After a bg process ends, cleanup the process using wait. 
NOTE: You may have to use SIGCHLD signal handler for this 
On termination of bg process, display its exit status.User should be able to run any number of background processes. 
• fg will bring a background process to foreground. 
  Only fg bring last background process, or fg will bring given pid to foreground
       • jobs will print all background process details.
7 Pipe functionality

1. Allow multiple processes communication by using pipes.
2. Create pipes and childs dynamically as per pipes passed from command-line
Eg: ls | wc, ls -l /dev | grep tty | wc -l
*/

#include "main.h"
/*
1.prompt (customisable input)
2. External command
3. Internal command
4. Special variables : echo$?--return value of previous program, echo $$-- pid of the Shell, echo $SHELL
path of the shell executable

*/
extern int last_return_value;
void echo(char* input)
{
    //input :\echo $$
    /*display the pid of mini shell (getpid())*/
    //inout $? --> print teh return value of previosu program
    //$SHELL ->print the nameof teh minshell (get_current_dir_name())
    //echo with nay string --> print that string
    char* args = input + 5;
    while(*args == ' ')args++;
    //check the special tokens 
    if(strcmp(args, "$$") == 0)
    {
        printf("%d\n", getpid());
    }
    else if(strcmp(args, "$$") == 0)
    {
        printf("%d\n", last_return_value);
    }
    else if(strcmp(args, "$SHELL"))
    {
        char* path = get_current_dir_name();
        if(path){
            printf("%s\n", path);
            free(path);
        }
    }
    else
    {
        printf("%s\n", args);
    }
}
void main()
{
    char input[50], prompt[50] = "minishell$";
    short int cmd_type;
    while(1)
    {
        printf("%s", prompt);
        fgets(input, 50, stdin);
        input[strcspn(input, "\n")] = 0; 
        if(!strcmp(input, "exit"))
        {
            return SUCCESS;
        }
        else if(!strncmp(input, "PS1=", 4)){
            //change the default promp tinto the NEW_PROMPTS
            strcpy(prompt, input+4);
        }else if((cmd_type = check_command_type(input)) == EXTERNAL)
        {
            execute_external_command(input);
        }else if(cmd_type == INTERNAL)
        {
            execute_internal_command(input);
        }else if(cmd_type == ECHO)
        {
            echo(input);//special variable
        }
    }



}
