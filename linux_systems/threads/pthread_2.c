#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
int counter = 0;
pthread_mutex_t lock;
void *print_X(void* arg)
{
    while(1)
    {
        printf("X\n");
        sleep(1);
    }
    return NULL;
}
void *print_O(void* arg)
{
    while(1)
    {
        printf("O\n");
        sleep(1);
    }
    return NULL;
}

int main()
{
    pthread_t tid1, tid2;
    pthread_mutex_init(&lock, NULL);
    pthread_create(&tid1, NULL, print_X, NULL);
    pthread_create(&tid2, NULL, print_O, NULL);
    pthread_join(tid1, NULL);
    pthread_join(tid2, NULL);
    pthread_mutex_destroy(&lock);
    printf("Back in main thrread\n");

}