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
#define INTERNAL 2
#define EXTERNAL 3
#define ECHO 4
#define YES 5
#define NO 6
void execute_external_command(char* input);
void execute_internal_command(char* input);
int check_command_type(char* input);
void echo(char* input);

#endif