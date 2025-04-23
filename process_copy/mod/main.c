#include <process_copy.h>

int main(int argc,char ** argv)
{
	int sfd,dfd;
	int pos = atoi(argv[3]);
	int blocksize = atoi(argv[4]);
	if((sfd = oprn(argv[1],O_RDONLY)) == -1) perror("open srcfile error");
	if((dfd = open(argv[2],O_WRONLY|O_CREAT,0755)) == -1) perror("open destfile error");
	lseek(sfd,pos,SEEK_SET);
	lseek(dfd,pos,SEEK_SET);

	char buffer[blocksize];
	bzero(buffer,sizeof(buffer));

	int len;
	len = read(sfd,buffer,sizeof(buffer));
	write(dfd,buffer,len);
	close(sfd);
	close(ded);
	return 0;
}
