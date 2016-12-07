# NCore's makefile
#
# Copyright 2016 Alejandro Linarez Rangel
# 
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
# 
#     http://www.apache.org/licenses/LICENSE-2.0
# 
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

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
OBJS=error.o ipcapi.o named_pipes.o dynamic_library.o
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

dynamic_library.o: $(WAPS)/dynamic_library.c $(HEADS)/$(WAPS)/dynamic_library.h
	$(CC) -o dynamic_library.o -c $(WAPS)/dynamic_library.c $(CFLAGS) $(CLIBS)

ipcapi.o: $(SRC)/ipcapi.c $(HEADS)/ipcapi.h
	$(CC) -o ipcapi.o -c $(SRC)/ipcapi.c $(CFLAGS) $(CLIBS)

clean:
	$(RM) $(TARGET) $(OBJS) $(MAIN) $(API)
