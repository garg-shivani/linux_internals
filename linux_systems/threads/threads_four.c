#include <stdlib.h>
#include <pthread.h>
#include <stdio.h>
pthread_mutex_t count_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t condition_var = PTHREAD_COND_INITIALIZER;

void functionCount1(void);
void functionCount2(void);
void functionCount3(void);
void functionCount4(void);
char count = 'h';
int c = 0;
#define COUNT_DONE 15

int main()
{
	pthread_t thread1, thread2, thread3, thread4;
	pthread_create(&thread1, NULL, functionCount1, NULL);
	pthread_create(&thread2, NULL, functionCount2, NULL);
    pthread_create(&thread3, NULL, functionCount3, NULL);
	pthread_create(&thread4, NULL, functionCount4, NULL);
	pthread_join(thread1, NULL);
	pthread_join(thread2, NULL);
    pthread_join(thread3, NULL);
    pthread_join(thread4, NULL);

	return 0;
}

// Print odd numbers
void functionCount1(void)
{
	for(;;) {
		// Lock mutex and then wait for signal to relase mutex
		pthread_mutex_lock( &count_mutex );
		if ( count == 's' ) {
			pthread_cond_wait( &condition_var, &count_mutex );
		}
		count = 's';
        c++;
		printf("Counter value functionCount1: %c\n",count);
		pthread_cond_signal( &condition_var );
		if ( c >= COUNT_DONE ) {
			pthread_mutex_unlock( &count_mutex );
			return NULL;
		}
		pthread_mutex_unlock( &count_mutex );
	}
}

// print even numbers
void functionCount2(void)
{
	for(;;) {
		// Lock mutex and then wait for signal to release mutex
		pthread_mutex_lock( &count_mutex );
		if ( count  == 'h' ) {
			pthread_cond_wait( &condition_var, &count_mutex );
		}
        count = 'h';
	    c++;

		printf("Counter value functionCount2: %c\n",count);
		pthread_cond_signal( &condition_var );
		if ( c >= COUNT_DONE ) {
			pthread_mutex_unlock( &count_mutex );
			return NULL;
		}
		pthread_mutex_unlock( &count_mutex );
	}
}
void functionCount3(void)
{
	for(;;) {
		// Lock mutex and then wait for signal to release mutex
		pthread_mutex_lock( &count_mutex );
		if ( count  == 'i' ) {
			pthread_cond_wait( &condition_var, &count_mutex );
		}
        count = 'i';
	    c++;

		printf("Counter value functionCount3: %c\n",count);
		pthread_cond_signal( &condition_var );
		if ( c >= COUNT_DONE ) {
			pthread_mutex_unlock( &count_mutex );
			return NULL;
		}
		pthread_mutex_unlock( &count_mutex );
	}
}
void functionCount4(void)
{
	for(;;) {
		// Lock mutex and then wait for signal to release mutex
		pthread_mutex_lock( &count_mutex );
		if ( count  == 'v' ) {
			pthread_cond_wait( &condition_var, &count_mutex );
		}
        count = 'v';
	    c++;

		printf("Counter value functionCount4: %c\n",count);
		pthread_cond_signal( &condition_var );
		if ( c >= COUNT_DONE ) {
			pthread_mutex_unlock( &count_mutex );
			return NULL;
		}
		pthread_mutex_unlock( &count_mutex );
	}
}