CC=g++
CFLAGS=-Wall -std=c++1z -O0
EXEC=brain

dist: all
all: rebuild

exec: build
	./brain

brain: src/main.cpp
	$(CC) -o $(EXEC) src/main.cpp $(CFLAGS)

clean:
	rm -rf *.o
	rm -f $(EXEC)

build: $(EXEC)

rebuild: clean build
