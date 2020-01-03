ifeq ($(DEBUG), true)
	CC = gcc -g
else
	CC = gcc
endif

all: main.o semaphore.o
	$(CC) -o control main.o 
	$(CC) -o write semaphore.o

main.o: main.c main.h
	$(CC) -c  main.c

shell.o: semaphore.c main.h
	$(CC) -c  semaphore.c

run:
	./program

clean:
	rm*.o
	rm*~