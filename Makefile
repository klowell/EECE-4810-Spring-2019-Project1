CC = gcc
CFLAGS = -std=c99 -Wall
OBJECTS = Project1.o test1.o test2.o test3.o test4.o test5.o
EXECS = Project1 test1 test2 test3 test4 test5

Project1.o: Project1.c
	$(CC) $(CFLAGS) -c Project1.c

test1.o: test1.c
	$(CC) $(CFLAGS) -c test1.c

test2.o: test2.c
	$(CC) $(CFLAGS) -c test2.c

test2: test2.o
	$(CC) test2.o -lm -o test2

test3.o: test3.c
	$(CC) $(CFLAGS) -c test3.c

test4.o: test4.c
	$(CC) $(CFLAGS) -c test4.c

test5.o: test5.c
	$(CC) $(CFLAGS) -c test5.c

clean:
	-rm $(OBJECTS) $(EXECS)