#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

void sigaction_handler(int signum, siginfo_t* info, void* dummy)
{
    printf("SIGINT arrived and the sender PID %d\n", info->si_pid);
}
int main()
{
    struct sigaction act, oldact;
    // act.sa_handler = signal_handler;
    act.sa_flags = SA_SIGINFO;
    act.sa_sigaction = sigaction_handler;
    //act new action to be updated for the signal
    //oldact - To collect the previous action.
    // sigaction(SIGINT, &act, &oldact);
    sigaction(SIGINT, &act, NULL);
    while(1)
    {
        printf("Inside main\n");
        sleep(1);
    }
}