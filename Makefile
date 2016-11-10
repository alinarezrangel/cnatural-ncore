
TARGET=ncore.out
API=libncore.a
FILES=ipcapi
WRAPOS=named_pipes
MAINF=main.c
DRIVERS=

CFLAGS=-std=c99 -Iinclude/ -Wall -g
LDFLAGS=
CLIBS=
LDLIBS=-ldl -lm
RM=rm
SRC=src
WAPS=wrap_os
HEADS=include
MAIN=main.o
OBJS=error.o ipcapi.o named_pipes.o
CC=gcc
LD=gcc

all: $(TARGET)

$(TARGET): $(API) $(MAIN)
	$(LD) -o $(TARGET) $(MAIN) $(API) $(LDFLAGS) $(LDLIBS)

$(API): $(OBJS)
	ar -cvq $(API) $(OBJS)

main.o: $(SRC)/main.c
	$(CC) -o main.o -c $(SRC)/main.c $(CFLAGS) $(CLIBS)

error.o: $(WAPS)/error.c $(HEADS)/error.h
	$(CC) -o error.o -c $(WAPS)/error.c $(CFLAGS) $(CLIBS)

named_pipes.o: $(WAPS)/named_pipes.c $(HEADS)/$(WAPS)/named_pipes.h
	$(CC) -o named_pipes.o -c $(WAPS)/named_pipes.c $(CFLAGS) $(CLIBS)

ipcapi.o: $(SRC)/ipcapi.c $(HEADS)/ipcapi.h
	$(CC) -o ipcapi.o -c $(SRC)/ipcapi.c $(CFLAGS) $(CLIBS)

clean:
	$(RM) $(TARGET) $(OBJS) $(MAIN) $(API)
