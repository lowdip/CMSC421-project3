#include <linux/kernel.h>
#include <linux/syscalls.h>
#include "buffer_sem.h"

static bb_buffer_421_t buffer;
struct semaphore mutex;
struct semaphore fill_count;
struct semaphore empty_count;
int previousValue; //Used to determine if the dequeue is being executed in improper order

SYSCALL_DEFINE0(init_buffer_sem_421) {
	//Initializes buffer
	struct bb_node_421 *previousNode;
	struct bb_node_421 *newNode;
	int i = 0;
	if(buffer.write!=NULL) {
		return -1;
	}
	//Constructs buffer
	while(i<SIZE_OF_BUFFER) {
		newNode = kmalloc(sizeof(struct bb_node_421),GFP_KERNEL);
		if(i==0) {
			buffer.read=newNode;
		} else {
			previousNode->next=newNode;
		}
		previousNode=newNode;
		i++;
	}
	//Intializes semaphores
	sema_init(&mutex,1);
	sema_init(&fill_count,0);
	sema_init(&empty_count,19);
	//Configures buffer
	previousNode->next=buffer.read;
	buffer.write=buffer.read;
	buffer.length = 0;
	previousValue = -1;
	return 0;
}


SYSCALL_DEFINE1(enqueue_buffer_sem_421, char*, data) {
	//Enqueues data
	struct bb_node_421 *editNode;
	int c = 0;
	if(buffer.write==NULL) {
		return -1;
	}
	//Increments empty_count
	down(&empty_count);
	editNode=buffer.write;
	//Copy data
	while(c<DATA_LENGTH-1) {
		(editNode->data)[c] = data[c];
		c++;
	}
	//Prints an error if it tries to queue past the capacity
	if(buffer.length>=20) {
		printk("Enqueue Error\n");
	}
	//Changes buffer
	down(&mutex);
	buffer.write=buffer.write->next;
	up(&mutex);
	buffer.length++;
	//Decrements fill count
	up(&fill_count);
	return 0;
}

SYSCALL_DEFINE1(dequeue_buffer_sem_421, char*, data) {
	//Dequeus buffer
	struct bb_node_421 *readNode;
	int c = 0;
	if(buffer.read==NULL) {
		return -1;
	}
	//Decrments fill count
	down(&fill_count);
	//Copy data
	readNode=buffer.read;
	while(c<DATA_LENGTH-1) {
		data[c]=(readNode->data)[c];
		c++;
	}
	//Gives a preview display of one of the numbers in the node dequeued which should all be the same number
	printk("%c",(readNode->data)[0]);
	//Prints an error if it tries to dequeue when there are no nodes
	if(buffer.length<=0) {
		printk("Dequeue Error\n");
	}
	previousValue++;
	if(previousValue==10) {
		previousValue = 0;
	}
	//Prints this message if dequeue is not executed properly
	if(previousValue!=((int)(readNode->data)[0]-48)) {
		printk("Error: Improper dequeue order\n");
	}
	//Changes buffer
	down(&mutex);
	buffer.read=buffer.read->next;
	up(&mutex);
	buffer.length--;
	//Decrements empty count
	up(&empty_count);
	return 0;
}

SYSCALL_DEFINE0(delete_buffer_sem_421) {
	// Tip: Don't call this while any process is waiting to enqueue or dequeue.
	//Deletes the buffer
	struct bb_node_421 *currentNode;
	struct bb_node_421 *next;
	int i = 0;
	if(buffer.read==NULL) {
		return -1;
	}
	currentNode = buffer.read;
	//Frees all the nodes in the buffer
	while(i<SIZE_OF_BUFFER) {
		next = currentNode->next;
		kfree(currentNode);
		currentNode=next;
		i++;
	}
	//Nulls the pointers
	buffer.read=NULL;
	buffer.write=NULL;
	previousValue = -1;
	//Semaphores do not need to be deleted
	return 0;
}
