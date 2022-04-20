//#include "buffer.h"
#include <stdio.h>
#include <linux/kernel.h>
#include <sys/syscall.h>
#include <unistd.h>
#define __NR_init_buffer_421 442
long init_buffer_421_syscall(void) {
	return syscall(__NR_init_buffer_421);
}
#define __NR_insert_buffer_421 443
long insert_buffer_421_syscall(int i) {
	return syscall(__NR_insert_buffer_421,i);
}
#define __NR_print_buffer_421 444
long print_buffer_421_syscall(void) {
	return syscall(__NR_print_buffer_421);
}
#define __NR_delete_buffer_421 445
long delete_buffer_421_syscall(void) {
	return syscall(__NR_delete_buffer_421);
}

int main() {
	printf("Print Buffer Test(returns -1):%li\n",print_buffer_421_syscall());
	printf("Delete Buffer Test(returns -1):%li\n",delete_buffer_421_syscall());
	printf("Insert Buffer Test(returns -1):%li\n",insert_buffer_421_syscall(5));
	printf("Initialization(returns 0):%li\n",init_buffer_421_syscall());
	printf("Initialization Test(returns -1):%li\n",init_buffer_421_syscall());
	int value = 1;
	if(print_buffer_421_syscall()!=0) {
		printf("Print error\n");
	}
	for(int i=0;i<20;i++) {
		if(insert_buffer_421_syscall(value)!=0) {
			printf("Insertion error\n");
		}
		value++;
		if(value==10) {
			value = 1;
		}
	}
	if(print_buffer_421_syscall()!=0) {
		printf("Print error\n");
	}
	printf("Loop Around Test(Should have 5 0's at the beginning):\n");
	for(int i=0;i<5;i++) {
		if(insert_buffer_421_syscall(0)!=0) {
			printf("Insertion error\n");
		}
	}
	if(print_buffer_421_syscall()!=0) {
		printf("Print error\n");
	}
	printf("Delete Buffer(returns 0):%li\n",delete_buffer_421_syscall());
	printf("Print Buffer Test(returns -1):%li\n",print_buffer_421_syscall());
	printf("Delete Buffer Test(returns -1):%li\n",delete_buffer_421_syscall());
	printf("Insert Buffer Test(returns -1):%li\n",insert_buffer_421_syscall(5));
	return 0;
}
