
TARGET=ncore.out
FILES=ipcapi
WRAPOS=named_pipes
MAINF=main.c

CFLAGS=-std=c99 -Iinclude/ -Wall -g
LDFLAGS=
CLIBS=
LDLIBS=-ldl -lm
RM=rm
SRC=src
WAPS=wrap_os
HEADS=include
OBJS=error.o ipcapi.o named_pipes.o main.o
CC=gcc
LD=gcc

all: $(TARGET)

$(TARGET): $(OBJS)
	$(LD) -o $(TARGET) $(OBJS) $(LDFLAGS) $(LDLIBS)

main.o: $(SRC)/main.c
	$(CC) -o main.o -c $(SRC)/main.c $(CFLAGS) $(CLIBS)

error.o: $(WAPS)/error.c $(HEADS)/error.h
	$(CC) -o error.o -c $(WAPS)/error.c $(CFLAGS) $(CLIBS)

named_pipes.o: $(WAPS)/named_pipes.c $(HEADS)/$(WAPS)/named_pipes.h
	$(CC) -o named_pipes.o -c $(WAPS)/named_pipes.c $(CFLAGS) $(CLIBS)

ipcapi.o: $(SRC)/ipcapi.c $(HEADS)/ipcapi.h
	$(CC) -o ipcapi.o -c $(SRC)/ipcapi.c $(CFLAGS) $(CLIBS)

clean:
	$(RM) $(TARGET) $(OBJS)
