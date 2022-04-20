#include "buffer_sem.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include <time.h>
#include <pthread.h>

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
		enqueue_buffer_421(data);
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
		dequeue_buffer_421(data);
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
	init_buffer_421();
	pthread_t consumer, producer;
	pthread_create(&producer,NULL,producer_fun,NULL);
	pthread_create(&consumer,NULL,consumer_fun,NULL);
	//Keeps main from continuing until both the consumer and producer thread are finished running
	pthread_join(producer,NULL);
	pthread_join(consumer,NULL);
	delete_buffer_421();
	return 0;
}
