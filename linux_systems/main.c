#include <stdio.h>
#include <signal.h>
#include <unistd.h>
void my_isr(int n)
{
    printf("I am the signal %d\n", n);
}
int main()
{
    printf("I am the process %d\n", getpid());
    signal(14, my_isr);
    raise(8);
    printf("HIa \n");
    while(1);
    return 0;
}