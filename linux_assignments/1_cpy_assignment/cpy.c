#include "main.h"
int check_file_exist(char* file)
{
    struct stat buffer;
    return (stat(file, &buffer));
}
int my_copy(int source_fd, int dest_fd)
{
    char buffer[4096];// ereading 4 KB memmory
    size_t bytes_read;
   while( (bytes_read = read(source_fd, &buffer,sizeof(buffer))) > 0)
   {
        write(dest_fd, &buffer , sizeof(buffer));
   }
   return 0;
}

int prompt_overwrite()
{
    char ch;
    printf("Do you want to overwrite (Y/n)? ");
    scanf(" %c", &ch);
    return (ch == 'Y' || ch == 'y');
}

int open_dest_file(char* dest, int overwrite)
{
    if(overwrite)
    {
        return open(dest, O_WRONLY | O_TRUNC);
    }
    else{
        return open(dest, O_WRONLY | O_CREAT | O_EXCL, 0666);
    }
}
int main(int argc, char* argv[])
{
    int src_fd = -1, dest_fd = -1;
    int s = 1,d = 2;
    int preserve_mode = 0;
    int overwrite = 0;
    umask(0022);//set the default file creation mask
    

    if(argc == 3)
    {
        s = 1;
        d = 2;
    }
    else if(argc == 4 && strcmp(argv[1], "-p" ) == 0)
    {
        
        s = 2;
        d = 3;
        preserve_mode = 1;
    }
    else
    {
        printf("Usage: ./my_copy [option] source_file destination file\n");
        return 0;
    }


    if(check_file_exist(argv[s]) != 0)
    {
        printf("Source file doesnot exist.\n");
        return 1;
    }
    src_fd = open(argv[s], O_RDONLY);
    if(src_fd <0)
    {
        perror("Error opening source file");
        return 1;
    }

    if(check_file_exist(argv[d]) == 0)
    {
        if(!prompt_overwrite())
        {
            close(src_fd);
            return 0;
        }
        else
        {
            overwrite = 1;
        } 
    }
    dest_fd = open_dest_file(argv[d], overwrite);
    if(dest_fd < 0)
    {
        perror("Error opening destination file");
        close(src_fd);
        return 1;
    }
    if(preserve_mode)
    {
        struct stat src_stat;
        if(fstat(src_fd, &src_stat) == 0)
        {
            fchmod(dest_fd, src_stat.st_mode);
        }
    }
    //below code is for copying th efile from fike descriptors
    if(my_copy( src_fd, dest_fd) == 0)
    {
        printf("File copied successfully\n");
    }
    else
    {
        printf("File not copied\n");
    }
    close(src_fd);
    close(dest_fd);
    
    return 0;
}