#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <time.h>
#include <dirent.h>
#include <fcntl.h>
#include <grp.h>
#include <sys/wait.h>
#include <unistd.h>


#include "commands.h"
#include "built_in.h"
#include <errno.h>

//export PATH=/usr/local/bin:/usr/bin:/bin:/usr/sbin:/sbin;

static struct built_in_command built_in_commands[] = {
  { "cd", do_cd, validate_cd_argv },
  { "pwd", do_pwd, validate_pwd_argv },
  { "fg", do_fg, validate_fg_argv }
};

static int is_built_in_command(const char* command_name)
{
  static const int n_built_in_commands = sizeof(built_in_commands) / sizeof(built_in_commands[0]);

  for (int i = 0; i < n_built_in_commands; ++i) {
    if (strcmp(command_name, built_in_commands[i].command_name) == 0) {
      return i;
    }
  }

  return -1; // Not found
}

/*
 * Description: Currently this function only handles single built_in commands. You should modify this structure to launch process and offer pipeline functionality.
 */
int evaluate_command(int n_commands, struct single_command (*commands)[512])
{
  if (n_commands > 0) {
    struct single_command* com = (*commands);

    assert(com->argc != 0);

    int built_in_pos = is_built_in_command(com->argv[0]);
    if (built_in_pos != -1) {
      if (built_in_commands[built_in_pos].command_validate(com->argc, com->argv)) {
        if (built_in_commands[built_in_pos].command_do(com->argc, com->argv) != 0) {
          fprintf(stderr, "%s: Error occurs\n", com->argv[0]);
        }
      } else {
        fprintf(stderr, "%s: Invalid arguments\n", com->argv[0]);
        return -1;
      }
    } else if (strcmp(com->argv[0], "") == 0) {
      return 0;
    } else if (strcmp(com->argv[0], "exit") == 0) {
      return 1;
    } 



//ls implementation
      else if(strcmp(com->argv[0], "/bin/ls") == 0) {


	int status;
	pid_t child_pid;
	pid_t parent_pid;

	if(fork() == 0)
		execv(com->argv[0], com->argv);
	else
		wait(&status);
    }



//process creation
     else if(strcmp(com->argv[0], "/bin/cat") == 0){

	int status;
//	int i=0;
	int dont_wait =0;
//	int pid = fork();
	//etc/hosts is the full path. edit late

		if(fork()==0){
//			execv(com->argv[0], com->argv);
			int i= 0;		
			while(com->argv[i] !=NULL) {
				if(strcmp(com->argv[i], "&")==0){

				dont_wait = 1;
				com->argv[i] = NULL;
			}
			i++;
			}

//child process and & signal
			if(dont_wait == 1){
//				execv(com->argv[0], com->argv);
				pid_t pid = getpid();
				printf("%d\n", pid);

				pid_t pid_running = waitpid(pid, &status, WNOHANG);

				if(pid_running == pid){
					printf("%d done\n", pid);
					return 1;
				}
				else
					do_fg(com->argc, com->argv);
				
				return 1;
			}

			else
				execv(com->argv[0], com->argv);
			
		//	if(
		}
			
		//	execv(com->argv[0], com->argv);
		else
			wait(&status);


//	else
//	 return 1;
     }

	else if(strcmp(com->argv[0], "/usr/bin/vim") ==0){

		int status;
		if(fork()==0)
			execv(com->argv[0], com->argv);
	
		else
			wait(&status);
//launch vim
	}


//implement path resolution. ls /, cat /etc/hosts, vim , cd ~
// export PATH = /usr/local.....



//background processing
/*	else if(com->argc>0){

		int i = 0;
		int dont_wait = 0;
		while(com->argv[i]!= NULL){
			if(!strcmp(com->argv[i], "&")){
				dont_wait = 1;
				com->argv[i] = NULL;
			}
			i++;
		}


		pid_t pid;
		pid = getpid();
		printf("%s", pid);

		
	}
*/
      else {
      fprintf(stderr, "%s: command not found\n", com->argv[0]);
      return -1;
    }

//using elsestrcmp(com->argv[0], "ls"
// ls/bin branch 
//vim


}

  return 0;
}

void free_commands(int n_commands, struct single_command (*commands)[512])
{
  for (int i = 0; i < n_commands; ++i) {
    struct single_command *com = (*commands) + i;
    int argc = com->argc;
    char** argv = com->argv;

    for (int j = 0; j < argc; ++j) {
      free(argv[j]);
    }

    free(argv);
  }

  memset((*commands), 0, sizeof(struct single_command) * n_commands);
}
