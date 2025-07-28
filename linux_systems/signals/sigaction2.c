#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

void signal_handler(int signum, siginfo_t* info, void* dummy)
{
    printf("Exit value of child processss is %d\n", info->si_status);
}
int main()
{
    struct sigaction act;
    act.sa_sigaction = signal_handler;
    act.sa_flags = SA_SIGINFO | SA_NOCLDWAIT;
    sigaction(SIGCHLD, &act, NULL);
    int pid = fork();
    if(pid > 0)
    {
        printf("This is parent process\n");
        pause();// It will block the execution of calling process untill a signal occurs.
        sleep(15); // sleep will get interrupt if signal occur
        printf("Parent terminated\n");
    }
    else if(pid == 0)
    {
        printf("Child is running\n");
        sleep(2);
        printf("Child terminated\n");
        exit(6);
    }

}