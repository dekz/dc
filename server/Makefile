CC=gcc
CFLAGS=-Wall -pthread -pedantic -std=gnu99 -g
COMMAND=$(CC) $(CFLAGS)

SRC=src/*.c
BIN=build/dc

all: compile run

compile: clean build_dir
	$(COMMAND) -o $(BIN) $(SRC)

run:
	$(BIN)

build_dir:
	mkdir build

clean:
	rm -rf build