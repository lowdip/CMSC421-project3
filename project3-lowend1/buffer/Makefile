# makefile for scheduling program
#
# make rr - for round-robin scheduling
# make fcfs - for FCFS scheduling
# make sjf - for SJF scheduling
# make priority - for priority scheduling
# make priority_rr - for priority with round robin scheduling

CC=gcc
CFLAGS=-Wall
obj-y := buffer.o
clean:
	rm *.o kernel test user

kernel: test.o
	$(CC) $(CFLAGS) -o kernel test.o

user: buffer_user.o test_user.o
	$(CC) $(CFLAGS) -o user buffer_user.o test_user.o

test_user.o: test_user.c
	$(CC) $(CFLAGS) -c test_user.c
	
test.o: test.c
	$(CC) $(CFLAGS) -c test.c
	
buffer_user.o: buffer.h buffer_user.c
	$(CC) $(CFLAGS) -c buffer_user.c
	
buffer.o: buffer.h buffer.c
	$(CC) $(CFLAGS) -c buffer.c
