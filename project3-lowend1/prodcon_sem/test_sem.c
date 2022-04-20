#include "buffer_sem.h"
#include <linux/kernel.h>
#include <sys/syscall.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include <time.h>
#include <pthread.h>

#define __NR_init_buffer_sem_421 446
long init_buffer_sem_421_syscall(void) {
	return syscall(__NR_init_buffer_sem_421);
}
#define __NR_enqueue_buffer_sem_421 447
long enqueue_buffer_sem_421_syscall(char* data) {
	return syscall(__NR_enqueue_buffer_sem_421,data);
}
#define __NR_dequeue_buffer_sem_421 448
long dequeue_buffer_sem_421_syscall(char* data) {
	return syscall(__NR_dequeue_buffer_sem_421,data);
}
#define __NR_delete_buffer_sem_421 449
long delete_buffer_sem_421_syscall(void) {
	return syscall(__NR_delete_buffer_sem_421);
}

void* producer_fun() {
	int value = 0;
	char exit[] = "Producer executed";
	//Runs enqueue 1000 times to test the dequeue buffer
	for(int i=0;i<1000;i++) {	
		char data[DATA_LENGTH+1];
		for(int c=0;c<DATA_LENGTH;c++) {
			data[c]=value+'0';
		}
		usleep(1000+rand()%9000);
		enqueue_buffer_sem_421_syscall(data);
		value++;
		if(value==10) {
			value=0;
		}
	}
	pthread_exit(exit);
}

void* consumer_fun() {
	int value = 0;
	char exit[] = "Consumer executed";
	//Runs dequeue 1000 times to test the dequeue buffer
	for(int i=0;i<1000;i++) {	
		char data[DATA_LENGTH+1];
		for(int c=0;c<DATA_LENGTH;c++) {
			data[c]=value+'0';
		}
		usleep(1000+rand()%9000);
		dequeue_buffer_sem_421_syscall(data);
		value++;
		if(value==10) {
			value=0;
		}
	}
	pthread_exit(exit);
}

int main() {
	time_t t;
	srand((unsigned) time(&t));
	init_buffer_sem_421_syscall();
	pthread_t consumer, producer;
	pthread_create(&producer,NULL,producer_fun,NULL);
	pthread_create(&consumer,NULL,consumer_fun,NULL);
	//Keeps main from continuing until both the consumer and producer thread are finished running
	pthread_join(producer,NULL);
	pthread_join(consumer,NULL);
	delete_buffer_sem_421_syscall();
	return 0;
}
