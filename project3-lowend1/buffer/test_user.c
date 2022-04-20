#include "buffer.h"
#include <stdio.h>
int main() {
	printf("Print Buffer Test(returns -1):%li\n",print_buffer_421());
	printf("Delete Buffer Test(returns -1):%li\n",delete_buffer_421());
	printf("Insert Buffer Test(returns -1):%li\n",insert_buffer_421(5));
	printf("Initialization(returns 0):%li\n",init_buffer_421());
	printf("Initialization Test(returns -1):%li\n",init_buffer_421());
	int value = 1;
	if(print_buffer_421()!=0) {
		printf("Print error\n");
	}
	for(int i=0;i<20;i++) {
		if(insert_buffer_421(value)!=0) {
			printf("Insertion error\n");
		}
		value++;
		if(value==10) {
			value = 1;
		}
	}
	if(print_buffer_421()!=0) {
		printf("Print error\n");
	}
	printf("Loop Around Test(Should have 5 0's at the beginning):\n");
	for(int i=0;i<5;i++) {
		if(insert_buffer_421(0)!=0) {
			printf("Insertion error\n");
		}
	}
	if(print_buffer_421()!=0) {
		printf("Print error\n");
	}
	printf("Delete Buffer(returns 0):%li\n",delete_buffer_421());
	printf("Print Buffer Test(returns -1):%li\n",print_buffer_421());
	printf("Delete Buffer Test(returns -1):%li\n",delete_buffer_421());
	printf("Insert Buffer Test(returns -1):%li\n",insert_buffer_421(5));
	return 0;
}
