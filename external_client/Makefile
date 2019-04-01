all:Client
Client: Client.o
	gcc -o Client Client.o

Client.o: Client.c Client.h
	gcc -c Client.c

clean:
	rm -f *.o Client
