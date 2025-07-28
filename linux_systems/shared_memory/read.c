#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#define KEY 0xA
int main()
{
    int shmid = shmget(KEY, 100, 0);
    if(shmid == -1)
    {
        perror("shmget");
        return -1;
    }
    char* ptr = shmat(shmid, NULL, 0);
    if(ptr == (char*)-1)
    {
        perror("shmat");
        return -1;
    } 
    printf("Data from shm %s\n", ptr);
    shmctl(shmid, IPC_RMID, NULL);
    sleep(10);
    shmdt(ptr);
    printf("Proecss detached\n");
    return 0;
}
/*
ipcrm ->ussed to delete shm segment
ipcm -m <shmid>  mentions the shmid wich needs to be deleted
ipcrm -M <key> mention the key which needs to be deleted

*/