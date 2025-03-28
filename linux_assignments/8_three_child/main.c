#include "main.h"
int main(int argc, char* argv[])
{
    int pid = fork();
    if( pid == 0)
    {
        //child1
        printf("Child1 with pid %d created\n", getpid());
        sleep(1);
    }
    else{
        //parent process
        int pid = fork();
        if( pid == 0)
        {
            //child1
            printf("Child2 with pid %d created\n", getpid());
            sleep(1);        
        }
        else{
            //parent process
            int pid = fork();
            if( pid == 0)
            {
                //child1
                printf("Child3 with pid %d created\n", getpid());        
                sleep(1);    
            }
            else{
                //parent process
                int status1, status2, status3;
                printf("Child %d is terminated with code %d\n",wait(&status1), WEXITSTATUS(status1));
                printf("Child %d is terminated with code %d\n",wait(&status2), WEXITSTATUS(status2));
                printf("Child %d is terminated with code %d\n",wait(&status3), WEXITSTATUS(status3));    
            }
        }
    } 
    return 0;
}

//Alternate method 
// #include <stdio.h>
// #include <unistd.h>
// #include <sys/wait.h>

// int main() {
//     printf("Parent (PID:%d) starts\n", getpid());

//     // Create 3 children
//     for (int i = 1; i <= 3; i++) {
//         if (fork() == 0) {
//             // Child process
//             printf("Child %d (PID:%d) running\n", i, getpid());
//             sleep(i);  // Each child sleeps for i seconds
//             printf("Child %d (PID:%d) exiting\n", i, getpid());
//             return i;  // Exit with status i
//         }
//     }

//     // Parent waits for all children
//     for (int i = 1; i <= 3; i++) {
//         int status;
//         pid_t child_pid = wait(&status);
//         printf("Parent: Child (PID:%d) exited with status %d\n", 
//                child_pid, WEXITSTATUS(status));
//     }

//     printf("Parent (PID:%d) done\n", getpid());
//     return 0;
// }