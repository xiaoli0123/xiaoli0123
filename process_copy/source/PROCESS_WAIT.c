#include <process_copy.h>

int PROCESS_WAIT(void)
{
	pid_t = pid;
	while((pid = waitpid(-1,NULL,WNOHANG)) != -1)
	{
		printf("parent wait zombie pid %d\n",pid);
	}
	return 0;
}
