#include <stdlib.h>
#include <stdio.h>
#include "buffer_sem.h"

static bb_buffer_421_t buffer;
static sem_t mutex;
static sem_t fill_count;
static sem_t empty_count;
int previousValue = -1; //Used to determine if the dequeue is being executed in improper order

long init_buffer_421(void) {
	//Initializes buffer
	if(buffer.write!=NULL) {
		return -1;
	}
	struct bb_node_421 *previousNode;
	//Constructs buffer
	for(int i=0;i<SIZE_OF_BUFFER;i++) {
		struct bb_node_421 *newNode = malloc(sizeof(struct bb_node_421));
		if(i==0) {
			buffer.read=newNode;
		} else {
			previousNode->next=newNode;
		}
		previousNode=newNode;
	}
	//Intializes semaphores
	sem_init(&mutex,0,1);
	sem_init(&fill_count,0,0);
	sem_init(&empty_count,0,19);
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
	//Increments empty_count
	sem_wait(&empty_count);
	struct bb_node_421 *editNode=buffer.write;
	//Copy data
	for(int c=0;c<DATA_LENGTH-1;c++) {
		(editNode->data)[c]=data[c];
	}
	//Prints an error if it tries to queue past the capacity
	if(buffer.length>=20) {
		printf("Enqueue Error\n");
	}
	//Changes buffer
	sem_wait(&mutex);
	buffer.write=buffer.write->next;
	sem_post(&mutex);
	buffer.length++;
	//Decrements fill count
	sem_post(&fill_count);
	return 0;
}

long dequeue_buffer_421(char * data) {
	//Dequeus buffer
	if(buffer.read==NULL) {
		return -1;
	}
	//Decrments fill count
	sem_wait(&fill_count);
	//Copy data
	struct bb_node_421 *readNode=buffer.read;
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
	sem_wait(&mutex);
	buffer.read=buffer.read->next;
	sem_post(&mutex);
	buffer.length--;
	//Decrements empty count
	sem_post(&empty_count);
	return 0;
}


long delete_buffer_421(void) {
	// Tip: Don't call this while any process is waiting to enqueue or dequeue.
	//Deletes the buffer
	if(buffer.read==NULL) {
		return -1;
	}
	struct bb_node_421 *currentNode = buffer.read;
	struct bb_node_421 *next;
	//Frees all the nodes in the buffer
	for(int i=0;i<SIZE_OF_BUFFER;i++) {
		next = currentNode->next;
		free(currentNode);
		currentNode=next;
	}
	//Nulls the pointers
	buffer.read=NULL;
	buffer.write=NULL;
	//Deletes the semaphores
	sem_destroy(&mutex);
	sem_destroy(&fill_count);
	sem_destroy(&empty_count);
	return 0;
}

void print_semaphores(void) {
	// You can call this method to check the status of the semaphores.
	// Don't forget to initialize them first!
	// YOU DO NOT NEED TO IMPLEMENT THIS FOR KERNEL SPACE.
	int value;
	sem_getvalue(&mutex, &value);
	printf("sem_t mutex = %d\n", value);
	sem_getvalue(&fill_count, &value);
	printf("sem_t fill_count = %d\n", value);
	sem_getvalue(&empty_count, &value);
	printf("sem_t empty_count = %d\n", value);
	return;
}
