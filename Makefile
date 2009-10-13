.PHONY : all clean server client

all: server client

clean:
	$(MAKE) -C server clean
	$(MAKE) -C client clean

server:
	$(MAKE) -C server

client:
	$(MAKE) -C client
