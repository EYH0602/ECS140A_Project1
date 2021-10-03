CC = g++ --std=c++11
CFLAGS = -g -Werror -Wall

INCS = rpn.h
OBJS = rpn.o

all: rpn main

rpn.o: rpn.cpp rpn.h
	$(CC) -c $(CFLAGS) rpn.cpp

main: $(OBJS) main.cpp
	$(CC) -o main $(OBJS) $(CFLAGS)
