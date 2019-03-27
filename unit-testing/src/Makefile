CC=gcc
CFLAGS=-werror -wall
#LFLAGS=
LIBS=-lcunit
SRCS= unittest.c
TARGET=unittest
OBJS=$(SRCS:.c=.o)
all:$(TARGET)
INCLUDES=-I../include/

$(TARGET):$(OBJS)
	$(CC) -o $(TARGET) $(OBJS) $(LIBS) #$(INCLUDES)
.c.o:
	$(CC) -c $(SRCS) #$(INCLUDES) 

clean:
	rm -f *.o $(TARGET)