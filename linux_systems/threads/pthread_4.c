#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
typedef struct 
{
    int n1, n2, res;
}data_t;
 

void* thread_function(void* arg)
{
    data_t *data = (data_t*)arg;
    data->res = data->n1 + data->n2;
    return NULL;
}

int main()
{   
    pthread_t tid;
    data_t data = {10, 20};
    pthread_create(&tid, NULL, thread_function, (void*) &data);
    pthread_join(tid, NULL);
    printf("Bck in main thread and the result is %d\n", data.res);
    return 0;
}