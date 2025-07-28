#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
void* thread_function(void* arg)
{
    int* ptr = (int*)arg;
    int* res = malloc(sizeof(int));
    // *res = ptr[0] + ptr[1];
    // return (void*)res;
    return (void*)(long)ptr[0] + ptr[1];//hacckway method//sizeof long depends on the system


}

int main()
{
    pthread_t tid;
    int data[] = {40, 20};
    int* res;
    pthread_create(&tid, NULL, thread_function, (void* )data);
    pthread_join(tid, (void**)&res);//collecting th ereturn value from thread
    printf("Back in main thread and the result - %d\n", *res);//
    free(res);
    return 0;
}


// typedef struct 
// {
//     /* data */
//     int data;
//     char ch;
//     double d;
// }data_t;

// void* thread_function(void* arg)
// {
//     data_t* p = (data_t*)arg;
//     printf("Data from main thread %d %c %lf\n", p->data, p->ch,p->d);
//     return NULL;
// }

// int main()
// {
//     pthread_t tid;
//     data_t data = {10, 'A', 10.2};
//     pthread_create(&tid, NULL, thread_function, (void*)&data);
//     pthread_join(tid, NULL);

//     printf("Back in main thread\n");
// }
