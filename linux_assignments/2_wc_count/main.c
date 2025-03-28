//implement wc command with -l -w -c
#include "main.h"

extern int optind;

void get_options(int argc, char*argv[], char* l_f, char* w_f, char* c_f)
{
    char ch;
    while((ch = getopt(argc, argv, "lwc")) != -1)
    {
        switch(ch)
        {
            case 'l':
                *l_f = 1;
                break;
            case 'w':
                *w_f = 1;
                break;
            case 'c':
                *c_f = 1;
                break;

        }
    }
    return;
}
void my_wc(int fd,  int *line_count, int* word_count, int* bytes_count)
{
    char buffer[4096];
    ssize_t bytes_read;
    bool in_word = false;
    *line_count = *word_count = *bytes_count=  0;
    while((bytes_read = read(fd, buffer, sizeof(buffer)))> 0)
    {
        *bytes_count += bytes_read;
        for(ssize_t i = 0;i<bytes_read;i++)
        {
            char c= buffer[i];
            //count lines
            if(c == '\n')
            {
                (*line_count)++;
            }
            //count_words
            if(isspace(c))
            {
                in_word = false;
            }
            else if(!in_word)
            {
                in_word = true;
                (*word_count)++;
            }
        }
    }
    return;
}



int main(int argc, char* argv[])
{
    int total_lines = 0, total_words = 0, total_bytes = 0;
    char l_f = 0, w_f = 0, c_f = 0;
    get_options(argc, argv, &l_f, &w_f, &c_f);
    if (!l_f && !w_f && !c_f) {
        l_f = w_f = c_f = 1;
    }
    if(argv[optind] != NULL)
    {
        int files = argc - optind;
        for(int i = optind; i<argc; i++)
        {
            int lines = 0, words = 0, bytes = 0;
            int fd = open(argv[i], O_RDONLY);
            if(fd < 0)
            {
                perror(argv[i]);
                continue;
            }
            my_wc(fd, &lines, &words, &bytes);
            close(fd);
            if(l_f) printf("%d ", lines);
            if(w_f) printf("%d ", words);
            if(c_f) printf("%d ", bytes);
            printf("%s\n", argv[i]);
            total_lines += lines;
            total_words += words;
            total_bytes += bytes;
        }
        if(files > 1)
        {
            if(l_f) printf("%d ", total_lines);
            if(w_f) printf("%d ", total_words);
            if(c_f) printf("%d ", total_bytes);
            printf("total\n");
        }
    }
    else
    {
       int lines = 0 ,words = 0,bytes = 0;
        my_wc(0, &lines, &words, &bytes);//0 is the file descritor for stdin
        if(l_f) printf("%d ", lines);
        if(w_f) printf("%d ", words);
        if(c_f) printf("%d ", bytes);
        printf("\n");
    }

    return 0;
}