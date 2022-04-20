#include "buffer_mon.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include <time.h>
#include <pthread.h>

void* producer_fun() {
	int value = 0;
	char exit[] = "Producer executed";
	for(int i=0;i<1000;i++) {	
		char data[DATA_LENGTH+1];
		for(int c=0;c<DATA_LENGTH;c++) {
			data[c]=value+'0';
		}
		//pthread_cond_wait(&cond, &wait);
		//pthread_mutex_lock(&mutex);
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
	for(int i=0;i<1000;i++) {	
		char data[DATA_LENGTH+1];
		for(int c=0;c<DATA_LENGTH;c++) {
			data[c]=value+'0';
		}
		usleep(10+rand()%9000);
		dequeue_buffer_421(data);
				value++;
		if(value==10) {
			value=0;
		}
	}
	pthread_exit(exit);
}

//Use a pthread condition
//When want to make things wait
//Set mutex lock
//Use pthread_cond_wait connected to condition
//When want to unlock
//Use pthread_cond_signal with the condition to unlock the wait

int main() {
	pthread_t consumer, producer;
	time_t t;
	srand((unsigned) time(&t));
	init_buffer_421();
	pthread_create(&producer,NULL,producer_fun,NULL);
	pthread_create(&consumer,NULL,consumer_fun,NULL);
	pthread_join(producer,NULL);
	pthread_join(consumer,NULL);
	//pthread_cond_t cond;
	//char data2[DATA_LENGTH+1];
	//dequeue_buffer_421(data2);
	//printf("%s",data2);
	delete_buffer_421();
	return 0;
}
