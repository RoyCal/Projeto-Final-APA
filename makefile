TARGET = main

CC = g++

CFLAGS = -Wall -Wextra -std=c++17

DEPS = grafo.h VND.h

OBJS = main.o grafo.o VND.o

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o output/$(TARGET)

main.o: main.cpp $(DEPS)
	$(CC) $(CFLAGS) -c main.cpp -o $@

grafo.o: grafo.cpp $(DEPS)
	$(CC) $(CFLAGS) -c grafo.cpp -o $@

VND.o: VND.cpp $(DEPS)
	$(CC) $(CFLAGS) -c VND.cpp -o $@

clean:
	rm -f $(TARGET) $(OBJS)

.PHONY: all clean
