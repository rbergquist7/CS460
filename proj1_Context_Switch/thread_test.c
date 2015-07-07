#include <stdio.h>
#include <stdlib.h>

//define thread struct
typedef struct
{
    void* stack_pointer;
    void (*initial_function) (void);
}thread_t;

//declare functions
void thread_start(thread_t * old, thread_t * new);
void thread_switch(thread_t * old, thread_t * new);
void yield();
void performYield();

//create 2 global threads
thread_t current_thread;
thread_t stored_thread;

//define yield function
void yield(){
    thread_t temp = current_thread;
    current_thread = stored_thread;
    stored_thread = temp;
    thread_switch(&stored_thread, &current_thread);
}

//define print function
void performYield(){
    //continuously run the following
    int i;
    // the iteration number of this for-loop can be changed for testing purposes
    for(i=0;i<50;i++){
        printf("%s\n", "current_thread: perform yield");
        yield();
    }
}

//test context switch
int main(void) {
    /* student to complete the logic in main here */
    
    // Program exits with segmentation fault for stack sizes
    // under 512
    
    int stack_size=1024;
    
    current_thread.stack_pointer =(void *)malloc(stack_size);
    current_thread.stack_pointer+=stack_size;
    
    // set performYield as the initial function of the current thread
    current_thread.initial_function = performYield;
    
    thread_start(&stored_thread, &current_thread);
    
    int i;
    
    // The number of for-loop printf iteration in main and performYield
    // can control which thread finishes first.
    // This test case finishes performYield first, and main fails to
    // find current_thread because it has ended. This results in a
    // segmentation fault error.
    
    for(i=0;i<95;i++)
    {
        printf("stored_thread: perform yield\n");
        yield();
    }
    
    return 0;
}
