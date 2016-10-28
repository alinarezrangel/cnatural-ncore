
TARGET=ncore.out
FILES=ipcapi
WRAPOS=named_pipes
MAINF=main.c

CFLAGS=-std=c99 -Iinclude/
LDFLAGS=
CLIBS=
LDLIBS=-ldl -lm
RM=rm
OBJS=$(addsufix .o,$(FILES))
SOURCES=$(addprefix src/,$(addsufix .c,$(FILES)))
OSFCN=$(addprefix wrap_os/,$(addsufix .c,$(WRAPOS)))
HEADERS=$(addprefix include/,$(addsufix .h,$(FILES)))

.SUFFIXES:

.SUFFIXES: .c .o

# Convert a dot C file to a dot O
.c.o:
	$(CC) -c $(CFLAGS) $(CLIBS) $<

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) -o $(TARGET) $(OBJS) $(LDFLAGS) $(LDLIBS)

$(OBJS): $(HEADERS) $(SOURCES) $(MAINF) $(OSFCN)

clean:
	$(RM) $(TARGET) $(OBJS)
