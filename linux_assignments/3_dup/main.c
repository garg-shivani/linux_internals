#include "main.h"
int using_dup(int fd)
{

    if (fd == -1) {
     perror("Error opening file");
        return 1;
     }
    int std_out_backup = dup(1);
    close(1);
     if(dup(fd) != 1)
     {
         perror("dup");
         exit(EXIT_FAILURE);
     }
     close(fd);
     printf("Print this message in File\n");
     fflush(stdout);
     dup2(std_out_backup, 1);
     printf("Print this message into STDOUT\n");
     close(std_out_backup);
     return 0;
}
int using_dup2(int fd)
{
    int stdout_copy = dup(1);
    if(dup2(fd, 1) == -1)
    {
        perror("dup2");
        exit(1);
    }
    close(fd);
    printf("Print this message into file\n");
    // fflush(1);
    //Restore the original stdout
    dup2(stdout_copy, 1);
    printf("Print this message into STDOUT\n");
    close(stdout_copy);
    return 0;
}
int main(int argc, char* argv[])
{  
    if(argc == 2)
    {
        int fd = open(argv[1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
        if(fd == -1)
        {
            perror("open");
            exit(1);
        }
       printf("menu :\n\t1.dup\n\t2. dup2\noption :");
       int i;
       scanf("%d", &i);
       switch (i)
       {
            case 1:
                using_dup(fd);
                break;
            case 2:
                using_dup2(fd);
                break;
       }

    }
    else
    {
        printf("Usage : ./a.out file_name\n");
    }
    return 0;
}