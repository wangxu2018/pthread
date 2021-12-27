# **C相关函数**

## **pthread_self**

	pthread_t pthread_self(void)
		功能：获取线程id，线程id是在进程地址空间内部，用来标识线程身份的id号
		返回值：本线程id

## **pthread_create**


	int pthread_create(pthread_t *tid, const pthread_attr_t *attr, void *(*start_rountn)(void *), void *arg)
		功能：创建子线程
	
		参1：传出参数。表新创建的子线程 id
		参2：线程属性。传NULL表使用默认属性
		参3：子线程回调函数。创建成功，ptherad_create函数返回时，该函数会被自动调用
		参4：参3的参数。没有的话，传NULL
	
		返回值：成功：0；失败：errno
	
	循环创建N个子线程：
	for （i = 0； i < 5; i++）{
	    pthread_create(&tid, NULL, tfn, (void *)i);   // 将 int 类型 i， 强转成 void *， 传参
	}

​	也可通过设置 attr 参数来设置线程属性，

```
typedef struct { 
    int detachstate;					// 线程的分离状态
    int schedpolicy;				// 线程调度策略
    struct sched_param schedparam;	 // 线程的调度参数
    int inheritsched;			    // 线程的继承性
    int scope; 					   // 线程的作用域
    size_t guardsize; 			   // 线程栈末尾的警戒缓冲区大小
    int stackaddr_set; 			   // 线程的栈设置
    void* stackaddr; 			   // 线程栈的位置
    size_t stacksize; 			   // 线程栈的大小,通过设置线程栈的大小来降低内存的使用,可以增加最大线程个数
} pthread_attr_t;

初始化线程属性：
	int pthread_attr_init(pthread_attr_t *attr)
	成功：0；失败：错误号
销毁线程属性所占用的资源:
	int pthread_attr_destroy(pthread_attr_t *attr)
	成功：0；失败：错误号	
```

​	举例1：设置线程分离属性，直接在创建的时候就为detach的

````
pthread_attr_t attr	创建一个线程属性结构体变量
pthread_attr_init(&attr)	初始化线程属性
pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED)	设置线程属性为 分离态
pthread_create(&tid, &attr, tfn, NULL)	借助修改后的 设置线程属性 创建为分离态的新线程
pthread_attr_destroy(&attr)	销毁线程属性所占用的资源
````

## **pthread_exit**


	void pthread_exit(void *retval)
		功能：退出当前线程。
		retval：退出值，无退出值时，NULL
	
	exit()：退出当前进程
	return: 返回到调用者那里去
	pthread_exit(): 退出当前线程

## **pthread_join**


	int pthread_join(pthread_t thread, void **retval)
		功能：阻塞回收线程
		参数：thread: 待回收的线程id
		参数：retval：传出参数。 回收的那个线程的退出值，线程异常借助，值为 -1。
		返回值：成功：0；失败：errno

## **pthread_detach**

	int pthread_detach(pthread_t thread)
		功能：设置线程分离，分离后的线程资源会被自动回收
		thread: 待分离的线程id
		返回值：成功：0；失败：errno	

## 	**pthread_cancel**

	int pthread_cancel(pthread_t thread)
		功能：杀死一个线程
		thread: 待杀死的线程id
		返回值：成功：0；失败：errno
		
	注：pthread_cancel需要到达取消点（保存点）,否则pthread_cancel无效，也可以不设置取消点，只要有与内核交互的函数即可，需要进内核然后才会被终止。也可以在程序中，手动添加一个取消点，使用 pthread_testcancel()。
	
	成功被 pthread_cancel() 杀死的线程，返回 -1，使用pthead_join 可以回收。



## **相关代码实现**

- **code/pthread_func.c**

  线程的功能函数使用

- **code/pthread_exit_return.c**

  - exit、return、pthread_exit三个函数的使用

- **code/pthread_join.c**

  - 回收线程的练习，以及子线程返回的参数获取

- **code/pthread_set_attr_detach.c**

  - 创建线程时设置为分离线程

- **code/pthread_set_child_pthread_stack_size.c**

  - 创建时动态设置创建的线程的栈的大小

