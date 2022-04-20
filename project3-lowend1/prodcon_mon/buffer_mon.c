#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include "buffer_mon.h"

static ring_buffer_421_t buffer;
pthread_mutex_t mutex;
pthread_cond_t enqueue;
pthread_cond_t dequeue;
int previousValue = -1;

long init_buffer_421(void) {
	//Initializes buffer
	if(buffer.write!=NULL) {
		return -1;
	}
	struct node_421 *previousNode;
	//Constructs buffer
	for(int i=0;i<SIZE_OF_BUFFER;i++) {
		struct node_421 *newNode = malloc(sizeof(struct node_421));
		if(i==0) {
			buffer.read=newNode;
		} else {
			previousNode->next=newNode;
		}
		previousNode=newNode;
	}
	//Intializes conditions and mutex
	pthread_mutex_init(&mutex, NULL);
	pthread_cond_init(&enqueue, NULL);
	pthread_cond_init(&dequeue, NULL);
	//Configures buffer
	previousNode->next=buffer.read;
	buffer.write=buffer.read;
	buffer.length = 0;
	return 0;
}


long enqueue_buffer_421(char * data) {
	//Enqueues data
	if(buffer.write==NULL) {
		return -1;
	}
	pthread_mutex_lock(&mutex);
	//Waits if buffer is full
	if(buffer.length>=20) {
		pthread_cond_wait(&enqueue,&mutex);
	}
	struct node_421 *editNode=buffer.write;
	//Copy data
	for(int c=0;c<DATA_LENGTH-1;c++) {
		(editNode->data)[c]=data[c];
	}
	//Prints an error if it tries to queue past the capacity
	if(buffer.length>=20) {
		printf("Enqueue Error\n");
	}
	//Changes buffer
	buffer.write=buffer.write->next;
	buffer.length++;
	//Releases wait for dequeue
	if(buffer.length<=1) {
		pthread_cond_signal(&dequeue);
	}
	pthread_mutex_unlock(&mutex);
	return 0;
}

long dequeue_buffer_421(char * data) {
	//Dequeus buffer
	if(buffer.read==NULL) {
		return -1;
	}
	pthread_mutex_lock(&mutex);
	//Waits if buffer is empty
	if(buffer.length<=0) {
		pthread_cond_wait(&dequeue,&mutex);
	}
	//Copy data
	struct node_421 *readNode=buffer.read;
	for(int c=0;c<DATA_LENGTH-1;c++) {
		data[c]=(readNode->data)[c];
	}
	//Gives a preview display of one of the numbers in the node dequeued which should all be the same number
	printf("%c",(readNode->data)[0]);
	//Prints an error if it tries to dequeue when there are no nodes
	if(buffer.length<=0) {
		printf("Dequeue Error\n");
	}
	previousValue++;
	if(previousValue==10) {
		previousValue = 0;
	}
	//Prints this message if dequeue is not executed properly
	if(previousValue!=(int)(readNode->data)[0]-48) {
		printf("Error: Improper dequeue order\n");
	}
	//Changes buffer
	//pthread_mutex_lock(&mutex);
	buffer.read=buffer.read->next;
	//pthread_mutex_unlock(&mutex);
	buffer.length--;
	//Releases wait for enqueue
	if(buffer.length>=19) {
		pthread_cond_signal(&enqueue);
	}
	pthread_mutex_unlock(&mutex);
	return 0;
}


long delete_buffer_421(void) {
	// Tip: Don't call this while any process is waiting to enqueue or dequeue.
	//Deletes the buffer
	if(buffer.read==NULL) {
		return -1;
	}
	struct node_421 *currentNode = buffer.read;
	struct node_421 *next;
	//Frees all the nodes in the buffer
	for(int i=0;i<SIZE_OF_BUFFER;i++) {
		next = currentNode->next;
		free(currentNode);
		currentNode=next;
	}
	//Nulls the pointers
	buffer.read=NULL;
	buffer.write=NULL;
	return 0;
}
