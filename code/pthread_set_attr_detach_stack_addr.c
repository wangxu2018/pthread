// 创建线程时设置为分离线程、并且根据属性设置创建线程栈内存的大小以及初始地址

#include <stdio.h>
#include <pthread.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#define SIZE 0x10000

void *th_fun(void *arg)
{
	while (1) {
		sleep(2);
	}
}

int main(void)
{
	pthread_t tid;
	int err, detachstate, i = 1;
	pthread_attr_t attr;
	size_t stacksize;   //typedef  size_t  unsigned int 
	void *stackaddr;

	pthread_attr_init(&attr);								// 初始化线程属性变量attr
	pthread_attr_getstack(&attr, &stackaddr, &stacksize);
	pthread_attr_getdetachstate(&attr, &detachstate);

	if (detachstate == PTHREAD_CREATE_DETACHED) {  			//默认是分离态
		printf("thread detached\n");
	} else if (detachstate == PTHREAD_CREATE_JOINABLE) {	//默认时非分离
		printf("thread join\n");
	} else {
		printf("thread un known\n");
	}

	pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);	// 设置线程分离属性

	while (1) {
		stackaddr = malloc(SIZE);									// 在堆上申请内存,指定线程栈的起始地址和大小
		if (stackaddr == NULL) {
			perror("malloc");
			exit(1);
		}
		stacksize = SIZE;
	 	pthread_attr_setstack(&attr, stackaddr, stacksize);			// 借助线程的属性,修改线程栈空间大小

		err = pthread_create(&tid, &attr, th_fun, NULL);
		if (err != 0) {
			printf("%s\n", strerror(err));
			exit(1);
		}
		sleep(2);
		printf("%d\n", i++);
	}

	pthread_attr_destroy(&attr);									// 销毁线程属性变量

	return 0;
}
