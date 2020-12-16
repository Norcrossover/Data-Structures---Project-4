CC = g++
CFLAGS = -g -Wall -std=c++11
OBJS = app.o mgr.o tree.o data.o

app: $(OBJS)

app.o: mgr.h tree.h data.h

mgr.o: tree.h data.h

tree.o: tree.h data.h

data.o: data.h

clean:
	rm app *.o
