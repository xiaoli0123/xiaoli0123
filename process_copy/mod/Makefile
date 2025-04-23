
INCLUDE_PATH=../include
LIBRARY_PATH=../library
CC=gcc
TARGET=copy
CFLAGS=-I$(INCLUDE_PATH) -c -g -Wall
SRCFILE=$(wildcrd *.c)
DESTFILE=$(patsubst %.c,%.o,$(SRCFILE))

$(TARGET):$(DESTFILE)
	$(CC) $^ -o $@


%.o:%.c
	$(CC) $(CFLAGS) $<

clean:
	rm $(DESTFILE) -rf
	rm $(TARGET) -rf
