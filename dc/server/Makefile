CC=gcc
CFLAGS=-Wall -pthread -pedantic -std=gnu99 -g
COMMAND=$(CC) $(CFLAGS)

SRC=src/*.c
BIN=build/server

all: clean build_dir
	$(COMMAND) -o $(BIN) $(SRC)

run:
	$(BIN)

build_dir:
	mkdir -p build

clean:
	rm -rf build