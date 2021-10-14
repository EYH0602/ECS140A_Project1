CC = g++ --std=c++11
CFLAGS = -Werror -Wall

INCS = rpn.h

rpn: $(OBJS) rpn.cpp
	$(CC) -o rpn $(CFLAGS) rpn.cpp

clean:
	rm -f *.o *~ rpn
