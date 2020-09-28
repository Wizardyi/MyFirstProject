#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <semaphore.h>

//线程函数 
void *thread_function(void *arg);

sem_t bin_sem;//信号量对象

#define WORK_SIZE 1024

char work_area[WORK_SIZE];//工作区

int pthread_test()
{
	int res;
	pthread_t a_thread;
	void *thread_result;

	res = sem_init(&bin_sem,0,0);//初始化信号量对象

	if(res)//初始化信号量失败
	{
		perror("Semaphore initialization failed\n");
		exit(EXIT_FAILURE);
	}

	//创建新线程
	res = pthread_create(&a_thread,NULL,thread_function,NULL);
	if(res)
	{
		perror("Thread creation failed\n");
		exit(EXIT_FAILURE);
	}

	printf("Input some text.Enter 'end' to finish\n");

	while(strncmp("end",work_area,3) != 0)
	{//输入没有结束
		fgets(work_area,WORK_SIZE,stdin);
		sem_post(&bin_sem);//给信号量值加一
	}

	printf("waiting for thread to finish\n");

	//等待子线程结束，收集子线程信息
	res = pthread_join(a_thread,&thread_result);
	if(res)
	{
		perror("Thread join failed\n");
		exit(EXIT_FAILURE);
	}

	printf("Thread joined\n");

	//销毁信号量对象
	sem_destroy(&bin_sem);

	exit(EXIT_SUCCESS);
}

void *thread_function(void *arg)
{
	sem_wait(&bin_sem);//将信号量值减一。

	while(strncmp("end",work_area,3))
	{
		printf("You input %lu characters\n",strlen(work_area) - 1);
		sem_wait(&bin_sem);
	}

	pthread_exit(NULL);//线程终止执行
}
