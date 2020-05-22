CC=gcc
DBFLAGS=-g

all: client.c  server.c
	make client
	make server

client: client.c
	$(CC) -o client client.c

server: server.c
	$(CC) -o server server.c

clean:
	rm client
	rm server
