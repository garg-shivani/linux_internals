#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define THREAD_COUNT 5
int* array;
int SUM = 0;
int MAX = 0;
pthread_mutex_t sum_mutex;
pthread_mutex_t max_mutex;
typedef struct{
    int start;
    int end;
}ThreadData;
int main()
{
    int n ;
    printf("Enter the arary size\n");
    scanf("%d", &n);
    if(n >= 500)
    {
        //store elements manulaly from 1 from  0th index
        array = (int*)malloc(sizeof(int) *n);
        printf("ENter %d elements\n", n);
        
        //share the work among equallly among  atleast 5 threads
        //create atleast 5 threads
        //find sum and max for array in threads
        //print SUM and MAX in main
        //SUM and MAX are global variables
    }
    else
    {
        printf("Enter valid arary sizw\n");
        return 0;
    }




    return 0;
}