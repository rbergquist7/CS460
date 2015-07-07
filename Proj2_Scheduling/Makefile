all: scheduler prime

scheduler:
	gcc thread_start.s thread_switch.s scheduler.c queue.c main_test_loop.c -o scheduler -g

prime:
	gcc thread_start.s thread_switch.s scheduler.c queue.c main_test_nthprime.c -o prime -g
clean:
	rm scheduler prime
