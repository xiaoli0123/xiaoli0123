#include <process_copy.h>

int PROCESS_CREATE(const char * src,const char * dest,int blocksize,int pronum)
{
	pid_t pid;
	int i;
	for(i = 0;i<pronum;i++)
	{
		pid = fork();
		if(pid == 0)
			break;
	}
	if(pid > 0){
		PROCESS_WAIT();
	}else if(pid == 0){
		int pos;
		pos = i*blocksize;
		char strpos[10];
		char strblocksize[10];
		sprintf(strpos,"%d",pos);
		sprintf(strblocksize,"%d",blocksize);
		execl("/home/colin/colinSoft/20240720/process/process_copy/mod/copy","copy",src,dest,strpos,strblocksize,NULL);
	}else{
		perror("fork call failed");
		exit(0);
	}
	return 0;
}
