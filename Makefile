CC=gcc
CFLAGS=-std=c99

TEST_STR=abcdefghijklmnopqrstuvwxyz


all: fifo pipe mmap

test: fifo_test pipe_test mmap_test

clean: fifo_clean pipe_clean mmap_clean


fifo: fifo_output fifo_read

fifo_test: fifo
	echo "${TEST_STR}" | ./fifo_output fifo.p &
	./fifo_read fifo.p | grep -q "^${TEST_STR}$$"
	echo fifo test passed

fifo_clean:
	rm -f fifo_output fifo_read fifo_output.o fifo_read.o fifo.p

fifo_output: fifo_output.o

fifo_read: fifo_read.o

fifo_output.o: tools.h

fifo_read.o: tools.h


pipe: pipe.o

pipe_test: pipe
	echo "${TEST_STR}" | ./pipe | grep -q "^${TEST_STR}$$"
	echo pipe test passed

pipe_clean:
	rm -f pipe pipe.o

pipe.o: tools.h


mmap: mmap_service mmap_watch

# mmap's test have some strange problems, i can't fix it

mmap_test: mmap
	timeout 5 ./mmap_service mmap.f &
	./mmap_watch mmap.f >/dev/null
	rm -f mmap.f
	echo mmap test passed

mmap_clean:
	rm -f mmap_service mmap_watch mmap_service.o mmap_watch.o mmap.f

mmap_service: mmap_service.o

mmap_watch: mmap_watch.o

mmap_service.o: tools.h

mmap_watch.o: tools.h
