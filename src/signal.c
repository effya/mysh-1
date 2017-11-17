#include "signal.h"
#include "signal_handlers.h"


void catch_sigint(int signalNo)
{


	signal(SIGINT, catch_sigint);
	if(signalNo == SIGINT)
		printf("received SIGINT\n");
	fflush(stdout);

	
  
}

void catch_sigtstp(int signalNo);
{

  pid_t pid;
  pid = fork();

  signal(SIGTSTP, &sigstop);
  kill(pid, SIGSTOP);
  fflush(stdout);
  // TODO: File this!
  if( pid == 0){
	signal(SIGTSTP, &sigstop);
}
 // if (signalNo == SIGTSTP)

}
