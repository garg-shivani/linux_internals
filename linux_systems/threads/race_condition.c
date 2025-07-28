#include <stdio.h>
#include <pthread.h>
int count = 0;
void *thread_function(void* arg)
{
    while(1)
    {
        count = 0;
        count+=5;
        count += 10;
        printf("%d %ld",count, pthread_self());
    }
}
int main()
{
    pthread_t tid1, tid2;
    pthread_create(&tid1 , NULL, thread_function, NULL);
    pthread_create(&tid2 , NULL, thread_function, NULL);

    pthread_join(tid1, NULL);
    pthread_join(tid2, NULL);
    printf("back in main thread\n");
    return 0;
}
