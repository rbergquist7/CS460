#include <stdio.h>
#include <stdlib.h>
#include "scheduler.h"

//find the nth prime number for large values of n (naive algorithm)
void find_nth_prime(void * n) 
{
	char * str = (char*) n;
	int i = 0;
	unsigned long j;
	unsigned long p;
	for(p = 2; i < atoi(str); p++) 
	{        
		for(j = 2; j < p; j++)
		{
			if (p % j == 0)
				break;	
			yield();				
		}
		if (j == p)
			i++; 
		yield();       		
	}       
	printf("Prime %sth is %lu\n", str, p-1);	
}


int main(void)
{
	scheduler_begin();
	thread_fork(find_nth_prime, (void*)"15000");
	// printf("%s\n", "thread main");
	thread_fork(find_nth_prime, (void*)"10000");
	// printf("%s\n", "thread main");
	thread_fork(find_nth_prime, (void*)"5000");
	// printf("%s\n", "thread main");
	thread_fork(find_nth_prime, (void*)"1000");
	scheduler_end(); 
	printf("%s\n", "main_thread: return");
}
