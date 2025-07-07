execute_internal_command(char* input)
{
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
