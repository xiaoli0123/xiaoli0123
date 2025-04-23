#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <sys/wait.h>


int BLOCK_CUR(const char * src , int pronum);//任务量计算
int PRAM_CHECK(const char * src , int pronum , int argc);//参数验证
int PROCESS_CREATE(const char * src , const char * dest , int blocksize , int pronum);//多进程创建与重载
int PROCESS_WAIT(void);//僵尸回收
