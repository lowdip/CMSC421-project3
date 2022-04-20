# makefile for scheduling program
#
# make rr - for round-robin scheduling
# make fcfs - for FCFS scheduling
# make sjf - for SJF scheduling
# make priority - for priority scheduling
# make priority_rr - for priority with round robin scheduling

CC=gcc -pthread
CFLAGS=-Wall

clean:
	rm test_mon *.o

test_mon: test_buffer_mon.o buffer_mon.o
	$(CC) $(CFLAGS) -o test_mon test_buffer_mon.o buffer_mon.o

test_buffer_mon.o: test_buffer_mon.c
	$(CC) $(CFLAGS) -c test_buffer_mon.c
	
buffer_mon.o: buffer_mon.h buffer_mon.c
	$(CC) $(CFLAGS) -c buffer_mon.c
