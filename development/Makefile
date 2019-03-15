PLATFORM = HOST
#PLATFORM = TARGET

ifeq ($(PLATFORM), HOST)
	CC = gcc
endif


ifeq ($(PLATFORM), TARGET)
	CC = arm-linux-gcc
endif


all: Client Server

	
Client: Client.c
	$(CC) Client.c -o Client -lpthread -lrt -g
	
Server: Server.c
	$(CC) Server.c -o Server -lpthread -lrt -g
	
clean:
	rm Client Server
	rm socketlog.txt