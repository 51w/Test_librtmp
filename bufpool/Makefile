##
CC = mips-linux-gnu-gcc
AR = mips-linux-gnu-ar

OBJS := bufpool.o
TARGET = bufpool

%.o:%.c
	$(CC) -I. -o $@ -c $^
	
$(TARGET):$(OBJS)
	$(AR) rc libbufpool.a $^
	
all:$(TARGET)

clean:
	rm *.a *.o
