#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/fcntl.h>
#include <pthread.h>
#include <signal.h>
#include <sys/mman.h>
#include <sys/wait.h>

int done = 0;
int bufferA_ready = 0;
int bufferB_ready = 0;

char bufferA[1024];
char bufferB[1024];

pthread_mutex_t lock;
pthread_cond_t condA;
pthread_cond_t condB;

void * t1(void* arg)
{
	FILE* fd = fopen("server.log",O_RDWR);
	while(1)
	{
		pthread_mutex_lock(&lock);
		if(fgets(bufferA,1024,fd) == NULL)
		{
			done = 1;
			pthread_cond_signal(&condA);
			pthread_mutex_unlock(&lock);
			break;
		}

		bufferA_ready = 1;
		pthread_cond_signal(&condA);
		pthread_mutex_unlock(&lock);

		pthread_mutex_lock(&lock);
		while(bufferA_ready)
		{
			pthread_cond_wait(&condA,&lock);
		}
		pthread_mutex_unlock(&lock);
	}
	fclose(fd);
	return NULL;

}

void * t2(void* arg)
{
	while (1) {
		pthread_mutex_lock(&lock);
		while (!bufferA_ready && !done)
			pthread_cond_wait(&condA, &lock);
		if (done && !bufferA_ready) 
		{
			pthread_cond_signal(&condB);
			pthread_mutex_unlock(&lock);
			break;
		}
	
		if(strncmp(bufferA,"XTAG",4) == 0)
		{
			strncpy(bufferB,bufferA,1024);
			bufferB_ready = 1;
			pthread_cond_signal(&condB);
		}
	
		bufferA_ready = 0;
		pthread_cond_signal(&condA);
		pthread_mutex_unlock(&lock);
	}
	return NULL;
}

void * t3(void* arg)
{
	FILE* fd = fopen("result.log",O_RDWR);
	while(1)
	{
		pthread_mutex_lock(&lock);
		while(!bufferB_ready && !done)
		{
			pthread_cond_wait(&condB,&lock);
		}
		if(done && !bufferB_ready)
		{
			pthread_mutex_unlock(&lock);
			break;
		}

		fprintf(fd,"%s",bufferB);
		bufferB_ready = 0;
		pthread_mutex_unlock(&lock);
	}

	fclose(fd);
	return NULL;
}

int main(void)
{
	pthread_mutex_init(&lock, NULL);
	
	pthread_cond_init(&condA, NULL);
	pthread_cond_init(&condB, NULL);
	
	pthread_t tid[3];
	pthread_create(&tid[0],NULL,t1,NULL);
	pthread_create(&tid[1],NULL,t2,NULL);
	pthread_create(&tid[2],NULL,t3,NULL);
	
	pthread_join(tid[0],NULL);
	pthread_join(tid[1],NULL);
	pthread_join(tid[2],NULL);

	pthread_mutex_destroy(&lock);
	pthread_cond_destroy(&condA);
	pthread_cond_deatroy(&condB);
	return 0;





}
