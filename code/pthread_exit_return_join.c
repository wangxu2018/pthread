// exit、return、pthread_exit三个函数的使用
// 回收线程的练习，以及子线程返回的参数获取

#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>


void *tfn1(void *arg)
{
	printf("thread 1 returning\n");

	return (void *)111;			// 退出到调用该函数的位置
}

void *tfn2(void *arg)
{
	printf("thread 2 exiting\n");
	pthread_exit((void *)222);	// 退出该线程
}

void *tfn3(void *arg)
{
	while (1) {

		// printf("thread 3: I'm going to die in 3 seconds ...\n");
		// sleep(1);
        pthread_testcancel(); 	// 自己添加取消点
	}

    return (void *)666;
}

int main(void)
{
	pthread_t tid;
	void *tret = NULL;

	pthread_create(&tid, NULL, tfn1, NULL);
	pthread_join(tid, &tret);							// tret为接受函数返回值，返回值类型为void *，因此需要用void ** 去接收
	printf("thread 1 exit code = %d\n\n", (int)tret);

	pthread_create(&tid, NULL, tfn2, NULL);
	pthread_join(tid, &tret);
	printf("thread 2 exit code = %d\n\n", (int)tret);

	pthread_create(&tid, NULL, tfn3, NULL);
    pthread_cancel(tid);								// 手动杀死线程
	pthread_join(tid, &tret);
	printf("thread 3 exit code = %d\n", (int)tret);

	return 0;
}

