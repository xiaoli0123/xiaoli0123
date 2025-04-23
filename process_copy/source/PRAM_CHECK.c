#include <process_copy.h>

int PRAM_CHECK(char* srcfile,int pronum,int argc)
{
	if(argc < 3)
	{
		perror("argc < 3");
		exit(0);
	}

	if(access(srcfile,F_OK)==-1)
	{
		perror("srcfile not found");
		exit(0);
	}

	if(pronum <= 5 || pronum > 100)
	{
		perror("pronum illegal");
		exit(0);
	}
	return 0;
}
