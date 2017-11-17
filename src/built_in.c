#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <pwd.h>
#include <glob.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
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
  pid_t pid = getpid();
  int status;

  if(tcsetpgrp(1, getpgid(pid)) ==0 ){

	kill(pid, SIGCONT);
	waitpid(pid, &status, WUNTRACED);
	printf("%d running", pid);
}

  
/*
  if(argc<2){
	printf("usage: fg <pid> \n");
	return -1;
  int status;
  pid_t pid;
  int job_id = -1;
}
pid = atoi(argv[1]);

if(kill(-pid, SIGCONT) <0) {

	printf("mysh: fg %d: job not found\n", pid);
	return -1;

}

tcsetpgrp(0,pid);

*/


  return 0;
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
