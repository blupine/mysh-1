#include "signal_handlers.h"
#include <signal.h>
#include <stdio.h>
#include "built_in.h"
void catch_sigint(int signalNo)
{
   signal(SIGINT, SIG_IGN);
}
 
void catch_sigtstp(int signalNo)
{
   signal(SIGTSTP, SIG_IGN);
}

void catch_bg_int(int siganlNo)
{
		printf("%d  done  %s\n", bgpid, bg_full_command);
		signal(SIGINT);
}
