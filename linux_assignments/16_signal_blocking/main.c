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



//handler
    //int i = 10;
    while(i--)
    {
        printf("in handler %d times\n", 10 -i);
        sleep(1);
    }
int main()
{   
    struct sigaction new_act;
    new_act.sa_mask = 
    //register the atleast 4 signals(SIGINT< SIGSTP< SIGUSAR1, SIGUSR2);




    return 0;
}