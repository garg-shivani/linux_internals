/*Requirements: 

1. Write a signal handler function for any signal, say SIGINT .
2. While its running inside handler (use loop) block other signals(atleast 3) being received . 
3. Use sa_mask from struct sigaction to set signals to be blocked (Refer man ). 
4. To create a signal set use variable of sigset_t. 
5. To add or remove signals from set use sigaddset, sigdelset functions (refer man). 
6. Process will receive blocked signals once its out from handler. 

Sample execution: 

 1. ./block_signal
      Process 2345 waiting for signal.. press ctrl + c from terminal. 
      SIGINT received  
Inside handler 
Inside handler 
. .
.....

2. Now open another terminal and send signal to process using kill command. 
Bash$ kill ­SIGUSR1 2345 
Bash$ kill ­SIGTERM 2345 
Bash$ kill ­SIGABRT 2345 
 
3. After exiting from handler will respond to blocked signal.*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>



void sigint_handler(){
    printf("SIGINT received\n");
    int i = 10;
    while(i--)
    {
        printf("in handler %d times\n", 10 -i);
        sleep(1);
    }
    printf("Exiting handler\n");
}
// Additional signal handlers
void sigusr1_handler(int signo) {
    printf("SIGUSR1 received after handler\n");
}

void sigterm_handler(int signo) {
    printf("SIGTERM received after handler\n");
}

void sigabrt_handler(int signo) {
    printf("SIGABRT received after handler\n");
}
int main()
{   
    struct sigaction new_act;
    sigset_t block_set;

    //create an empty signal set
    sigemptyset(&block_set);
    //add signals to block while inside the handler
    sigaddset(&block_set, SIGUSR1);
    sigaddset(&block_set, SIGTERM);
    sigaddset(&block_set, SIGABRT);

    //assign handler
    new_act.sa_handler = sigint_handler;
    //set the sa_mask to block the above signals during handler exception

    new_act.sa_mask = block_set;
    //register the atleast 4 signals(SIGINT< SIGSTP< SIGUSAR1, SIGUSR2);
    new_act.sa_flags = 0;
    //register the SIGINT signal with the handler
    if(sigaction(SIGINT, &new_act, NULL) == -1)
    {
        perror("sigaction");
        exit(1);
    }
    //also register emty signal handlers fof rthe others signals so that theuy can be deliverd
    // Register signal handlers for the other signals
    signal(SIGUSR1, sigusr1_handler);
    signal(SIGTERM, sigterm_handler);
    signal(SIGABRT, sigabrt_handler);
    //print pid for sending siganls
    printf("Proccess %d waiting for signals Press ctrl+c to send SIGINT\n", getpid());
    //keep the process alive to receive signals
    while(1)
    {
        pause();
    }
    return 0;
}