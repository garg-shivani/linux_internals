#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
void signal_handler(int signum)
{
    int i = 10;
    while(--i)
    {
        printf("%d signal inside main\n", signum);
        sleep(1);
    }
}
int main()
{
    struct sigaction act, oldact;
    act.sa_handler = signal_handler;
    sigemptyset(&(act.sa_mask));//making the set to empty 
    sigaddset(&(act.sa_mask), SIGINT);//adding the signal to be blocked in the set, when ano
    //signal come in between it will not get interrupted.

    sigaction(SIGINT, &act, &oldact);
    sigaction(SIGTSTP, &act, &oldact);
    while(1)
    {
        printf("Inside the main\n");
        sleep(1);
    }


    return 0;
}
