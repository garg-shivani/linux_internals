#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
struct fact
{
    int start;
    int end;
};
void* factorial(void* arg)
{
    
    struct fact* range = (struct fact*) arg;
    unsigned long* fact = malloc(sizeof(unsigned long));
    *fact = 1;
    for(int i = range->start;i<= range->end;i++)
    {
        *fact = (*fact) * i;
    }
    return (void*)(fact);
}
int main()
{
    int n ;
    printf("Enter a number\n");
    scanf("%d", &n);
    int r = n / 3;// 7% 3 = 2
    int rem = n %3;
    struct fact var[3];
    int start = 1;
    for(int i =0;i<3;i++)
    {
        int len = r + ((i<rem)? 1: 0);
        var[i].start = start;
        var[i].end = start + len - 1;
        start = var[i].end + 1;
    }
    pthread_t tid[3];
    for(int i =0;i<3;i++)
    {
      
        pthread_create(&tid[i], NULL, factorial, &var[i]);
    }
    unsigned long result = 1;
    for(int i = 0;i<3;i++)
    {
        //wait for thread;
        void* res;
        pthread_join(tid[i], &res);
        result *=*(unsigned long*)res;
        free(res);
    }
    printf("factorial of %d is %lu\n", n, result);
    return 0;
}