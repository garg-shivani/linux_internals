#include "main.h"
int main(int argc, char* argv[])
{
    if(argc == 2)
    {
       
       int fd = open(argv[1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
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
        printf("Print this message into STDOUT");
        close(std_out_backup);
    }
    else
    {
        printf("Usage : ./a.out file_name\n");
    }
    return 0;
}