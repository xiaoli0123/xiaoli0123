#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/fcntl.h>
#include <pthread.h>
#include <signal.h>

int blocksize;
int sfd;
int dfd;
int offsets[381];

char* src_path;
char* dest_path;

int check_pram(int argc,int thread_num,char * src_file)
{
	if(argc < 3)
	{
		printf("pram number error\n");
		exit(0);
	}
	if(thread_num < 5||thread_num > 381)
	{
		printf("thread_num failed\n");
		exit(0);
	}
	if(access(src.file,F_OK) != 0)
	{
		printf("file not exist\n");
		exit(0);
	}
	return 0;
}

int block_cur(char * src_file,int thread_num)
{
	int fd = open(src_file,O_RDWR);
	int size = lseek(fd,0,SEEK_END);
	close(fd);
	if(size % thread_num == 0)
	{
		return size / thread_num;
	}else{
		return size / thread_num +1;
	}
}

int thread_create(int thread_num)
{
	pthread_t tid[thread_num];

	for(int i = 0;i<thread_num;i++)
	{
		offsets[i] = i*blocksize;
		if(pthread_create(&tid[i],NULL,thread_copy,(void*)&offsets[i]) != 0)
		{
			perror("pthread_create error");
			exit(1);
		}
	}

	for(int i = 0;i<thread_num;i++)
	{
		pthread_join(tid[i],NULL);
	}
	return 0;
}


void* thread_copy(void* arg)
{
	// src,dest,blocksize,pos(拷贝偏移量)
	int offset = *(int*)arg;

	char* buf = malloc(blocksize);
	if(!buf)
	{
		perror("malloc error");
	}
	int sfd_local = open(src_path,O_RDONLY);
	int dfd_local = open(dest_path,O_WRONLY);
	
	lseek(sfd_local,offset,SEEK_SET);
	lseek(dfd_local,offset,SEEK_SET);

	int len = read(sfd_local,buf,blocksize);
	if(len > 0)
	{
		write(dfd_local,buf,len);
	}
	close(sfd_local);
	close(dfd_local);
	free(buf);
	pthread_exit(NULL);
}

int main(int argc,char** argv)
{
	int thread_num;
	if(argc < 4){
		thread_num = 5;
	}else{
		thread_num = atoi(argv[3]);
	}
	check_pram(argc,thread_num,argv[1]);
	src_path = argv[1];
	dest_path = argv[2];
	blocksize = block_cur(argv[1],thread_num);
	// 打开源文件创建目标文件
	sfd = open(argv[1],O_RDONLY);
	dfd = open(argv[2],O_WRONLY|O_CREAT,0664);
	thread_create(thread_num);

	return 0;
}















