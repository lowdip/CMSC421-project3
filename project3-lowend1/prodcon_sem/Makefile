# makefile for scheduling program
#
# make rr - for round-robin scheduling
# make fcfs - for FCFS scheduling
# make sjf - for SJF scheduling
# make priority - for priority scheduling
# make priority_rr - for priority with round robin scheduling

CC=gcc -pthread
CFLAGS=-Wall
obj-y := buffer_sem.o

clean:
	rm user_sem sem *.o

user_sem: buffer_user_sem.o test_user_sem.o
	$(CC) $(CFLAGS) -o user_sem buffer_user_sem.o test_user_sem.o

test_user_sem.o: test_user_sem.c
	$(CC) $(CFLAGS) -c test_user_sem.c
	
buffer_user.o: buffer_sem.h buffer_user_sem.c
	$(CC) $(CFLAGS) -c buffer_user_sem.c
	
sem: test_sem.o
	$(CC) $(CFLAGS) -o sem test_sem.o

test_sem.o: test_sem.c
	$(CC) $(CFLAGS) -c test_sem.c
	
buffer_sem.o: buffer_sem.h buffer_sem.c
	$(CC) $(CFLAGS) -c buffer_sem.c
