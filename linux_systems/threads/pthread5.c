#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

void* thread_function(void* arg)
{
    int num = 5;
    while(num--)
    {
        printf("Thread is executing\n");
        sleep(1);
    }
    //void pthread_exit(void* ret);
    pthread_exit(NULL);//It will terminate the calling thread//whatever we want to 
    //return that value can be passed.
}


int main()
{
    pthread_t tid;
    //creating attribute object
    pthread_attr_t attr;
    //Initialize the attr object
    pthread_attr_init(&attr);
    //set detach state
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);

    pthread_create(&tid, &attr, thread_function, NULL);
    pthread_join(tid, NULL);//not blocking 
    printf("Back in main thread, main terminated\n");
    pthread_attr_destroy(&attr);
    //main terminated , and aothe thread also gets terminated.
    //because of this pthread_exit even if main i sterminated other threads
    //are executed.
    pthread_exit(NULL);//void pthread_exit(void* retval);
    return 0;
}