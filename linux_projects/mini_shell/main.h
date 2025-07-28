#ifndef MAIN_H
#define MAIN_H
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>
#define SUCCESS 0
#define FAILURE -1
#define EXTERNAL 0
#define INTERNAL 1
#define ECHO 2
void execute_external_command(char* input);
void execute_internal_command(char* input);
int check_command_type(char* input);
void signal_handler(int sig_num);
#endif