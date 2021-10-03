CC = g++ --std=c++11
CFLAGS = -Werror -Wall

INCS = rpn.h
OBJS = rpn.o

all: main

rpn.o: rpn.cpp rpn.h
	$(CC) -c $(CFLAGS) rpn.cpp

main: $(OBJS) main.cpp
	$(CC) -o main $(OBJS) $(CFLAGS) main.cpp

clean:
	rm -f *.o *~ main
