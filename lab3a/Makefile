CC = g++
CFLAGS = -c -Wall
XXFLAGS = -lgtest -lpthread

all: prog3A test

prog3A: main.o dialog.o
	$(CC) -o prog3A main.o dialog.o -Llib -ltrain

test: test.cpp
	$(CC) test.cpp -o test $(XXFLAGS)

main.o: main.cpp
	$(CC) $(CFLAGS) main.cpp

dialog.o: dialog.cpp
	$(CC) $(CFLAGS) dialog.cpp

clean:
	rm -rf *.o prog3A
