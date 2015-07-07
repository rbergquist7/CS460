#void thread_start(thread_t * old, thread_t * new);

.globl thread_start

thread_start:
	#push all callee-save registers onto the current stack
	pushq %rbx
	pushq %rbp
	pushq %r12
	pushq %r13
	pushq %r14
	pushq %r15

	#save the current stack pointer (%rsp) in old's thread table entry 
	movq %rsp, (%rdi)

	#load the stack pointer from new's thread table entry into %rsp
	movq (%rsi), %rsp

	#store thread_finish in stack
	pushq $thread_finish
	movq 16(%rsi), %rdi

	#jump to initial function of new
	jmp *8(%rsi)
