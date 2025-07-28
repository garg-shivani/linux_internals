execute_internal_command(char* input)
{
    //1. cd 2. exit 3. pwd 4. jobs 5. fg 6. bg
    //cd == int chdir(const char *path)
    //pwd==> char* get_current_dir_name(void);
    //jobs ==> Display pending processes with teh status
    //fg ==> Resume the recently stopped prpcess in the foreground
    //bg ==> Resume the recently stopped process in the background
  char* command = strtok(input, " \n");
  if(!strcmp(command, "cd")
  {
    char* path = strtok(NULL, " \n");
    if(path == NULL) path = getenv("HOME");
    if(chdir(path) != 0) perror("cd failed");
  }
  else   if(!strcmp(command, "pwd")
  {
    char cwd[1024];
    if(getcwd(cwd, sizeof(cwd)) != NULL)
      printf("%s\n", cwd);
    else
      perror("pwd failed");
  }
  else   if(!strcmp(command, "jobs")
  {
    
  }
  else   if(!strcmp(command, "fg")
  {}
  else   if(!strcmp(command, "bg")
  {}
}