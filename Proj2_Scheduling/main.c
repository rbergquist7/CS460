#include <stdio.h>
#include <stdlib.h>
#include "scheduler.h"

//perform loop from 0 until n-1
void loop(void * n) 
{
    char * str = (char*) n;//n is also ID of a thread (assume: different values of n for threads)
	int i;

	for (i = 0;i< atoi(str);i++)
	{
		printf("thread %s: step %d\n", str,i);
		yield();
	}
	printf("thread %s: DONE\n", str);
}

  
int main(void)
{
	scheduler_begin();
    thread_fork(loop, (void*)"8");
	printf("%s\n", "thread main");
	thread_fork(loop, (void*)"6");
	printf("%s\n", "thread main");
	thread_fork(loop, (void*)"4");
	printf("%s\n", "thread main");
	thread_fork(loop, (void*)"2");
    scheduler_end(); 
	printf("%s\n", "main_thread: return");
}
