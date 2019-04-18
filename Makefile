CC = gcc
CFLAGS = -Wall -ansi -pedantic -g
MAIN = guess
OBJS = guess.o funcs.o
all : $(MAIN)

$(MAIN) : $(OBJS) funcs.h
	$(CC) $(CFLAGS) -o $(MAIN) $(OBJS)

guess.o : guess.c funcs.h
	$(CC) $(CFLAGS) -c guess.c

funcs.o : funcs.c funcs.h
	$(CC) $(CFLAGS) -c funcs.c

clean :
	rm *.o $(MAIN) core