//used to communicate between any number of processes
//it is  a bidirectional communication
//how reading and wrting is happening with respect to fifo

/*
    using ptrs we can od the communication
    fastest
    data can be read multiple times
    Data naturally synchronised(Race condition)
    race condition: When muktiple process trying to access the shared resourcews at the same time 
    it may lead to data corruption , called as race condition
    shmget
    shmat
    read/write
    every shared memoeyr having shared memory id whihc is also having a key value
    1. shmget(key_t key, size_t size, int shmflg)
        ->int shmid = shmget(IPC_PRIVATE, 100, IPC_CREAT):
            always creates a new shm segment and returns that id 
        -> int shmid = shmget(0xa, 100, IPC_CREAT);
           checks is threr ay SHM ssegment associated with the key value
           if no, cretes a new SHM segment, otherwise return the ID of existing SHM segment

        ->int shmid = shmget(0xa, 100, 0);
        -> check only for existing SHM segment which is associated with the given key value
        ->if present return sthe id, otherwise returns -1
    2. Attach SHM
     void* ptr =  shmat(int shmid, void* shmddr, int shmflg)
     Attach the shm associate dwuth shmid to the address psace o fthe calling proces
     shmaddr = NULL, system itself will choose th ememory to attach the SHM segment
     shmaddr != NULL, and shmflag = SHM_RND , then atatch occurs at the address specified by the shmaddr
     on succcess, it will retunr the addr where SHM segment is attached.asm

    3. REad/write
     data = 10
     *(int*)ptr = data
     data = 20
     *((int*)ptr + 1) = 20

     char* str = "hello"
     strcpy(ptr, str);
     scanf("%s", ptr);
    read and display :
        puts(ptr);
        printf("%s\n", ptr);
        printf("%D\N", ptr);
    4. Dteach SHM:
     int shmdt(void* shmaddr);
     ->deteacch shared segment from the calling process
    5. Remove and delete SHM
     shmctl --<sysytem V shared memory control
     performs the control operation sepcifoed by cmd on the system V share dmemory segemnt hose
     indentifier is given in shmid.


*/
#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <string.h>

#define KEY 0xA
int main()
{
    int shmid = shmget(KEY, 100, IPC_CREAT | 0666);
    if(shmid == -1)
    {
        perror("shmget");
        return -1;
    }
    //attaching the process
    char* ptr = shmat(shmid, NULL, 0);
    if(ptr == (char*)-1)
    {
        perror("shmat");
        return -1;
    }
    printf("Enter the string : ");
    scanf("%[^\n]", ptr);
    printf("Write operation is successfull\n");
    shmdt(ptr);
    return 0;
}

