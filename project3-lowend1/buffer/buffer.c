//#include <stdlib.h>
#include <linux/kernel.h>
#include <linux/syscalls.h>
#include "buffer.h"

static ring_buffer_421_t buffer;

SYSCALL_DEFINE0(init_buffer_421) {
	struct node_421 *previousNode;
	struct node_421 *newNode;
	int i=0;
	if(buffer.write!=NULL) {
		return -1;
	}
	while(i<SIZE_OF_BUFFER) {
		newNode = kmalloc(sizeof(struct node_421),GFP_KERNEL);
		newNode->data=0;
		if(i==0) {
			buffer.read=newNode;
		} else {
			previousNode->next=newNode;
		}
		previousNode = newNode;
		i++;
	}
	previousNode->next=buffer.read;
	buffer.write=buffer.read;
	return 0;
}


SYSCALL_DEFINE1(insert_buffer_421, int, i) {
	if(buffer.write==NULL) {
		return -1;
	}
	buffer.write->data=i;
	buffer.write=buffer.write->next;
	return 0;
}

SYSCALL_DEFINE0(delete_buffer_421) {
	struct node_421 *currentNode;
	struct node_421 *next;
	int i=0;
	if(buffer.read==NULL) {
		return -1;
	}
	currentNode = buffer.read;
	while(i<SIZE_OF_BUFFER) {
		next = currentNode->next;
		kfree(currentNode);
		currentNode = next;
		i++;
	}
	buffer.read=NULL;
	buffer.write=NULL;
	return 0;
}

SYSCALL_DEFINE0(print_buffer_421) {
	struct node_421 *currentNode;
	struct node_421 *next;
	int i=0;
	printk("Start of Print");
	if(buffer.read==NULL) {
		return -1;
	}
	currentNode = buffer.read;
	while(i<SIZE_OF_BUFFER) {
		next = currentNode->next;
		printk("%i",currentNode->data);
		currentNode = next;
		i++;
	}
	printk("End of Print");
	return 0;
}
