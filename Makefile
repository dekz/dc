CC=gcc
CFLAGS=-Wall -pthread -pedantic -std=gnu99 -g
COMMAND=$(CC) $(CFLAGS)

SSRC=server/src/*.c
SBIN=server/build/
CSRC=client/src/*.c
CBIN=client/build/

all: compile run

compile: clean build_dir
	$(COMMAND) -o $(SBIN) $(SSRC)
	$(COMMAND) -o $(CBIN) $(CSRC)

run:
	$(SBIN)
	$(CBIN)

build_dir:
	mkdir server/build
	mkdir client/build

clean:
	rm -rf server/build
	rm -rf client/build