.PHONY: all start stop clean

all: fifo_server fifo_client

start: fifo_server fifo_client
	./fifo_server &
	./fifo_client &
	echo

stop:
	killall fifo_server
	killall fifo_client
	sleep 1
	echo

clean:
	rm fifo_server fifo_client

# Compile common.c with fifo_server & fifo_client.
CFLAGS += common.c
