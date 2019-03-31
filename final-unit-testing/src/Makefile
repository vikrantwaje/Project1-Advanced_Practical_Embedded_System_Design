CC=gcc
CFLAGS=-werror -wall
#LFLAGS=
LIBS=-lcunit -lrt
SRCS= unittest.c main.c ipc.c temp_sensor.c
TARGET=unittest
OBJS=$(SRCS:.c=.o)
all:$(TARGET)
INCLUDES=-I../include/

$(TARGET):$(OBJS)
	$(CC) -o $(TARGET) $(OBJS) $(LIBS) -lpthread $(INCLUDES) 
.c.o:
	$(CC) -c $(SRCS) $(INCLUDES) 

clean:
	rm -f *.o $(TARGET)
	rm -f *.xml