#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>

//handler
    //print the address of the seg fault using si_addr
    //terminate the program
void segfault_handler(int seg, siginfo_t *si, void* unused)
{
    printf("Segmentation fault...!!!\nAddress: %p caused error\n", si->si_addr);
    exit(EXIT_FAILURE);
}
int main()
{
    //reggiter the signal SIGSEGV sing sigaction
    //write a code for cerate seg fault
    struct sigaction sa;
    memset(&sa, 0, sizeof(sa));
    sa.sa_sigaction = segfault_handler;
    sa.sa_flags = SA_SIGINFO;
    //register SIGSEGV siganl with sigaction
    if(sigaction(SIGSEGV, &sa, NULL) == -1)
    {
        perror("Sigaction");
        exit(EXIT_FAILURE);
    }
    //intentionally create a segmentation fault
    char* str = "hello";;
    *str = 'H';//code segment data modification , is it possiblr?

    return 0;
}