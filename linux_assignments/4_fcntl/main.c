#include "main.h"

int main(int argc, char*argv[])
{
    int n1 = 150;
    int n2 = 100;
    if(argc != 2)
    {
        printf("Insufficient arguments\n");
        return 0;
    }
    int pid = fork();
    int fd = open(argv[1], O_WRONLY | O_CREAT |O_TRUNC,0644  );
    if(fd == -1)
    {
        perror("Error opening file\n");
        return 0;
    }
    pid_t pid = fork();
    if(pid == -1)
    {
        perror("Error opening fork proces");
        close(fd);
        return 0;
    }

    if(pid > 0)
    {
       lock_file(fd);
       print_prime_numbers(n1, fd);
       unlock_file(fd);
       wait(NULL);
    }
    else
    {
        lock_file(fd);
        print_fibbonacci_numbers(n1, fd);
        unlock_file(fd);
    }
    close(fd);
    return 0;
}