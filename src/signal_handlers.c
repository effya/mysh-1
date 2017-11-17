#include "signal_handlers.h"
#include <stdio.h>
#include <signal.h>



void catch_sigint(int signalNo)
{
  // TODO: File this!

  signal(SIGINT, catch_sigint);
  printf("cannot be terminated using ctrl c\n");
  fflush(stdout);

}

void catch_sigtstp(int signalNo)
{
  // TODO: File this!

  signal(SIGTSTP, catch_sigtstp);

}
