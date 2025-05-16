#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/fcntl.h>
#include <pthread.h>
#include <signal.h>

void* thread_wk(void* arg)
{
	// 普通线程代码
	int count = *(int *)arg;
	printf("thread 0x%x runing arg = %d\n",(unsigned  int)pthread_self(),count);
	while(1)
		sleep(1);
	return NULL;
}

int main(void)
{
	// 主控线程代码
	pthread_t tid;
	int count = 1024;
	int err;
	if((err = pthread_create(&tid,NULL,thread_wk,(void *)&(count))) > 0)
	{
		printf("pthread_create error:%s\n",strerror(err));
	}

	printf("master tid 0x%x,create thread tid 0x%x\n",(unsigned int)pthread_self(),(unsigned int)(tid));

	// 主线程等待所有线程执行完毕再退出
	while(1)
		sleep(1);
	return 0;
}
