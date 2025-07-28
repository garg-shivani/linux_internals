#include <stdio.h>
#include <time.h>
int main()
{
    time_t ret_value, my_time;
    ret_value = time(&my_time);
    if(ret_value == -1)
    {   
        printf("Time system call Failed\n");
        return 1;
    }
    printf("Time since epoch:%s\n", ctime(&ret_value));
    printf("Time since epoch:%ld\n", my_time);

    return 0;


}