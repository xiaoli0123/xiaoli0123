#include <processcopy.h>

int BLOCK_CUR(char* srcfile,int pronum)
{
	int fd = open(srcfile,O_RDWR);
	int filesize = lseek(fd,0,SEEK_END);
	close(fd);
	if(filesize % pronum == 0)
	{
		return filesize / pronum;
	}else
	{
		return filesize / pronum + 1;
	}
}
