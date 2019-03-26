CC=arm-linux-gcc
CFLAGS=-g
LFLAGS=
LIBS=-lpthread -lrt -lm
SRCS= main.c thread.c timer.c temp_sensor.c light_sensor.c logger.c synchronization.c server.c ipc.c
TARGET=main
OBJS=$(SRCS:.c=.o)
all:$(TARGET)
INCLUDES=-I../include/

$(TARGET):$(OBJS)
	$(CC) -o $(TARGET) $(OBJS) $(LIBS) $(INCLUDES)
.c.o:
	$(CC) -c $(SRCS) $(INCLUDES) 

clean:
	rm -f *.o $(TARGET)
