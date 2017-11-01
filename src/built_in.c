#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <unistd.h>
#include <linux/limits.h>

#include "built_in.h"


int do_cd(int argc, char** argv) {
  if (!validate_cd_argv(argc, argv))
    return -1;
  if (chdir(argv[1]) == -1)
    return -1;

  return 0;
}

int do_pwd(int argc, char** argv) {
  if (!validate_pwd_argv(argc, argv))
    return -1;

  char curdir[PATH_MAX];

  if (getcwd(curdir, PATH_MAX) == NULL)
    return -1;

  printf("%s\n", curdir);

  return 0;
}

int do_fg(int argc, char** argv) {
  if (!validate_fg_argv(argc, argv))
    return -1;

  // TODO: Fill this.

  return 0;
}

int do_exec(char** argv){ // argv[0]이 실행 가능한 파일일 경우
   if(fork()==0)
       execv(argv[0], argv);
    wait(0);   
}

int validate_cd_argv(int argc, char** argv) {
  if (argc != 2) return 0;
  if (strcmp(argv[0], "cd") != 0) return 0;

  struct stat buf;
  stat(argv[1], &buf);

  if (!S_ISDIR(buf.st_mode)) return 0;

  return 1;
}

int validate_pwd_argv(int argc, char** argv) {
  if (argc != 1) return 0;
  if (strcmp(argv[0], "pwd") != 0) return 0;

  return 1;
}

int validate_fg_argv(int argc, char** argv) {
  if (argc != 1) return 0;
  if (strcmp(argv[0], "fg") != 0) return 0;
  
  return 1;
}

char* getFullDirectory(char** argv)
{
//  printf("argv[0] : %s\n", argv[0]);
//  printf("argv[1] : %s\n", argv[1]);
  if(!access(argv[0],X_OK))
    return argv[0];
  const char *path = getenv("PATH");
  char* p = malloc(strlen(path));
  strcpy(p, path);
//  printf("path : %s\n", path);
  char *parsed_path = strtok(p, ":");
//  printf("after parsing path : %s\n", path); 
  while(parsed_path != NULL)
  {
 //   printf("와일뤂\n");
    char * dir = malloc(strlen(parsed_path) + strlen(argv[0]) + 1 );
    strcpy(dir, parsed_path);
    strcat(dir, "/");
    strcat(dir, argv[0]);
   // printf("made dir : %s\n", dir);
    if(!access(dir, X_OK)){
      argv[0] = malloc(strlen(dir)+1);
      strcpy(argv[0], dir);
    //  printf("parsed loop, argv[0]: %s\n", argv[0]);
      return argv[0];
    }
   // printf("%s\n", parsed_path);
    parsed_path = strtok(NULL, ":");
  }
  return NULL;
}
