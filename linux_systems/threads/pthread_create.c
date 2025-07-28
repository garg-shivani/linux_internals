#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
void* thread_function(void* arg)
{
    int i = 5;
    while(i--)
    {
        printf("Thread is excuting and tid - %ld\n", pthread_self());
        sleep(1);
    }
    return NULL;
}

int main()
{
    pthread_t tid;
    if(pthread_create(&tid, NULL, thread_function, NULL) != 0)
    {
        printf("thread not created\n");
        return -1;
    }
    //sleep(5);
    /*int pthread_join(pthread_t tid, void ** retval);
    -Block the excution of the calling thread until tid completes the execution.tid
    -It is also used to collect the return value of the thread
    -After the completion o fthread, it will clean up the thread dresources

    
    */
   pthread_join(tid, NULL);

    printf("Back in main thread\n");
    return 0;
}