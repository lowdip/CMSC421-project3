#include <stdlib.h>
#include <stdio.h>
#include "buffer.h"

static ring_buffer_421_t buffer;

long init_buffer_421(void) {
	if(buffer.write!=NULL) {
		return -1;
	}
	struct node_421 *previousNode;
	for(int i=0;i<SIZE_OF_BUFFER;i++) {
		struct node_421 *newNode = malloc(sizeof(struct node_421));
		newNode->data=0;
		if(i==0) {
			buffer.read=newNode;
		} else {
			previousNode->next=newNode;
		}
		previousNode = newNode;
	}
	previousNode->next=buffer.read;
	buffer.write=buffer.read;
	return 0;
}


long insert_buffer_421(int i) {
	if(buffer.write==NULL) {
		return -1;
	}
	buffer.write->data=i;
	buffer.write=buffer.write->next;
	return 0;
}

long delete_buffer_421(void) {
	if(buffer.read==NULL) {
		return -1;
	}
	struct node_421 *currentNode = buffer.read;
	struct node_421 *next;
	for(int i=0;i<SIZE_OF_BUFFER;i++) {
		next = currentNode->next;
		free(currentNode);
		currentNode = next;
	}
	buffer.read=NULL;
	buffer.write=NULL;
	return 0;
}

long print_buffer_421(void) {
	if(buffer.read==NULL) {
		return -1;
	}
	struct node_421 *currentNode = buffer.read;
	struct node_421 *next;
	for(int i=0;i<SIZE_OF_BUFFER;i++) {
		next = currentNode->next;
		printf("%i",currentNode->data);
		currentNode = next;
	}
	printf("\n");
	return 0;
}
