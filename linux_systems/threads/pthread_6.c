#include <stdio.h>
#include <pthread.h>
int count;
void* thread_function(void* arg)
{
    while(1)
    {
        count = 0;
        count += 5;
        count += 10;
        printf("%d tid - %lu\n", count, pthread_self());
    }
}

int main()
{
    pthread_t tid, tid2;
    pthread_create(&tid, NULL, thread_function, NULL);
    pthread_create(&tid2, NULL, thread_function, NULL);
    pthread_join(tid, NULL);
    pthread_join(tid2, NULL);
    printf("Back in main thread\n");
}