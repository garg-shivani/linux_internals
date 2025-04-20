#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>

/*
Requirements: 

1. User gives the time and date from command-line arguments.
2. Validate the time eg: Do not go behind the current time.
3. Date is an option, if user not providing date consider it as today.
4. In handler, avoid all user communication(printf, scanf etc) and loops. Make it minimal as possible.
 5. After the alarm expires, display a ALARM message along with date and time.
6. Prompt the user whether he wants to stop or sanooze.
7. If user selects stop, terminate the program.
8. If user selects snooze, prompt for snooze time in minutes. If user enters the time, reset the alarm to the entered time in minutes .If user doesn't enter time, default the snooze time to 1 mins
 
Sample execution: 


1. ./alarm (No arguments) 
Error: No arguments passed
Usage: ./alarm  [dd/mm/yy] 

2. ./alarm 30:15 

Error: Invalid time 

3. ./alarm 22:10 

set alarm for 10:10 PM for today 

4. ./alarm 22:10 02/03/16

set alarm for 10:10 PM for today 

5. When alarm occurs 

Wake­up...Alarm..!! 

1. Snooze     2. Exit 

if user select 1

 Enter snooze time :2 

( After 2 mins above process will repeat until user gives exit)
*/
// in handler ()
    //make flag as 1
#define _XOPEN_SOURCE
int alarm_triggered = 0;
void alarm_handler(int sig)
{
    alarm_triggered = 1;
}
int main(int argc, char* argv[])
{
    if(argc<2)
    {
        printf("Error:no args passed\n");
        printf("Usage: ./alarm [dd/mm/yy]\n");
        exit(1);
    }    
    time_t cur_time = time(NULL);
    struct tm user_tm; 
    
    memset(&user_tm, 0, sizeof(struct tm));
    if (strptime(argv[1], "%H:%M:%S", &user_tm) == NULL &&
        strptime(argv[1], "%H:%M", &user_tm) == NULL) {
        printf("Error: Invalid time format\n");
        exit(1);
    }
    
    if(argc == 2)
    {
        // char now_str[100];
        struct tm *cur = localtime(&cur_time);  
        // strftime(now_str, sizeof(now_str), "%H:%M:%S %d/%m/%Y", cur);
        // printf("Current system time: %s\n", now_str); 
        user_tm.tm_mday = cur->tm_mday;
        user_tm.tm_mon = cur->tm_mon;
        user_tm.tm_year = cur->tm_year;
    }
    else
    {
        strptime(argv[2], "%d/%m/%y", &user_tm);
    }
   

    time_t user_in = mktime(&user_tm);
    time_t alarm_time = user_in - cur_time;
    if(alarm_time <= 0)
    {
        printf("Enter valid time\n");
        exit(1);
    }
    //print the alrm time
    char formatted[100];
    strftime(formatted, sizeof(formatted), "%I:%M %p on %d/%m/%Y", &user_tm);
    printf("Alarm set for %s\n", formatted);
    //register SIGALARM signal using sigaction
    struct sigaction sa;
    sa.sa_handler = alarm_handler;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;
    sigaction(SIGALRM, &sa, NULL);
    alarm((unsigned int)alarm_time);
    while(1){
       if(alarm_triggered)
       {
            alarm_triggered = 0;
            //print the menu 
            printf("Wake up... Alarm..!!\n");
            int choice = 0;
            printf("1. Snooze\n2. Exit\nEnter your choice: ");
            scanf("%d", &choice);
            int c;
            while ((c = getchar()) != '\n' && c != EOF);
            if(choice == 2)
            {
                printf("Exiting alarm.\n");
                break;
            }
            else if(choice == 1)
            {
                //read user option
                //if user chooses option 1
                //read the snooze time in secs
                //set the alarm
                //id user choose option 2
                //terminate
                int snooze = 1;
                printf("Enter snooze time (in minutes) [default 1]: ");
                char line[10];
             
                if(fgets(line, sizeof(line), stdin))
                {
                    int val = atoi(line);
                    if(val > 0)
                    {
                        snooze = val;
                    }
                }
                printf("Snoozing for %d minute(s)...\n", snooze);
                alarm(snooze * 60);
            }
            else
            {
                printf("Invalid choice. Exiting.\n");
                break;
            }
        }
        pause();
    }
    return 0;
}