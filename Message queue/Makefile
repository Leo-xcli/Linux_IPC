.PHONY:all
all:client server

client:client.c common.h
	gcc -o $@ $^ -lpthread
server:server.c common.h
	gcc -o $@ $^ -lpthread
.PHONY:clean
clean:
	rm -f Client Server
