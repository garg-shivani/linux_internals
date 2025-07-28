/*
any thread can sem do sem_wait , sem_post;
bianry semaphore can be used , but in case of mutex
the process whihc has lock th eprocess has allowed to unlock it 
critical section: race condition is common in multi threading and multiprocssing environment
since both of them offer concurrency
and common resource facility, it wil raise to raise conditions

however the common resourcec can be differnet . In case
of multiple threads a common resource can be data segment/global variable
which is shared resource between multiple threads.
in case of processes, a common resource can be shared memory
/**********
Wait operation:
- decerements the value of semaphore by 1.
- if the value is already zero, the opreation blocks until the 
value of teh semaphore becomes positive.
- When the semaphore's value becomes positive, it is decremneted by 1 , 
and wait operation returns. 
post operation:
- increments the value of the sempahore by 1.asm
- if the semaphore was previosuly zero, and the threads are blocked in
wait opearation on that semaphore.
- one of those threads is unblocked and its wait operation completss (whihc brings
 the semaphore's value back to zero)
 Producer Consumer example:

* /
 */


#include <stdio.h>
#include <semaphore.h>
#include <pthread.h>
#define MAX_BUFF 10
void* consume(void* arg);
void *produce(void* arg);
int buf[MAX_BUFF], front , rear;
/*Here lock is used to cerate a critcial section
full and empty used to signalling events to other threads

*/
sem_t lock, full, empty;
int main()
{
    pthread_t tid1, tid2;
    /*lock is a binary semaphore used to make critical section same as mutex
    to make sure only one thread accessing at a time
    */
    sem_init(&lock, 0, 1);
    /*full is used to check queue is empty or not*/
    sem_init(&full, 0, 0);
    /*empty is used to check queue is full or not
    */
   sem_init(&empty, 0, 2);
   pthread_create(&tid1, NULL, produce, NULL);
   pthread_create(&tid2, NULL, consume, NULL);
   pthread_join(tid1, NULL);
   pthread_join(tid2, NULL);
    return 0;
}
void* produce(void* arg)
{
    int i ;
    for(i =0;i<10;i++)
    {
        /*now this is same as is_queue full()
        before storing value in queue*/
        sem_wait(&empty);
        sem_wait(&lock);
        printf("produced item is %d\n", i);
        buf[(++rear)%MAX_BUFF] = i;
        sem_post(&lock);
        /*this is to inform consumer that data is available in queue*/
        sem_post(&full);
    }
    return NULL;
}
void* consume(void* arg)
{
    int item , i;
    for(i =0;i<10;i++)
    {
        /*wat until data is available in the queue sameas is_queue_empty()*/
        sem_wait(&full);
        sem_wait(&lock);
        item = buf[(++front) % MAX_BUFF];
        printf("consumed item is %d\n", item);
        sem_post(&lock);
        /*notifyiing consumer that dat ais consumed and is available*/
        sem_post(&empty);
    }
}