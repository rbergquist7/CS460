#include <stdio.h>
#include <stdlib.h>

#include "queue.h"
#include "scheduler.h"

struct thread_t* old_thread; //added
struct thread_t* current_thread;
struct queue ready_list;
int stack_size = 10000;
int thread_count = 0; //added

void scheduler_begin()
{
    //initialize and/or allocate any data structures needed, set to running state
    current_thread = (struct thread_t*)malloc(sizeof(struct thread_t));
    current_thread->state = RUNNING;
}

void scheduler_end()
{
    //while threads exist, call yield
    while(thread_count > 0)
    {
        yield();
    }
}

/*encapsulates everything necessary to allocate a new thread and then jump to it*/
void thread_fork(void(*target)(void*), void * arg)
{
    //adding new thread, increase count
    thread_count++;
    //set current thread to old thread
    old_thread = current_thread;
    //set new thread to ready state, not yet running
    current_thread->state = READY;
    //enqueue pointer to new current thread
    thread_enqueue(&ready_list, current_thread);
    //new thread, must allocate new space in memory
    current_thread = (struct thread_t*)malloc(sizeof(struct thread_t));
    //set new thread to running state
    current_thread->state = RUNNING;
    //get memory needed for thread, set up current thread for execution
    current_thread->stack_pointer = (void*)malloc(stack_size);
    current_thread->stack_pointer += stack_size - 1;
    current_thread->initial_arg = arg;
    current_thread->initial_function = target;
    //start thread
    thread_start(old_thread, current_thread);
}

/*decrease thread count, set current thread to DONE since finished, and yield*/
void thread_finish()
{
    thread_count--;
    current_thread->state = DONE;
    yield();
}

/*pulling next thread to run off ready list, do not create new thread*/
void yield()
{
    old_thread = current_thread;
    current_thread = thread_dequeue(&ready_list);
    if(old_thread->state != DONE)
    {
        old_thread->state = READY;
        thread_enqueue(&ready_list, old_thread);
    }
    current_thread->state = RUNNING;
    thread_switch(old_thread, current_thread);
}
