
TARGET=ncore.out
FILES=
CFLAGS=-std=c99
LDFLAGS=
CLIBS=
LDLIBS=-ldl -lm
RM=rm
OBJS=$(addsufix .o,$(FILES))
SOURCES=$(addprefix src/,$(addsufix .c,$(FILES)))
HEADERS=$(addprefix include/,$(addsufix .h,$(FILES)))

.SUFFIXES:

.SUFFIXES: .c .o

# Convert a dot C file to a dot O
.c.o:
	$(CC) -c $(CFLAGS) $(CLIBS) $<

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) -o $(TARGET) $(OBJS) $(LDFLAGS) $(LDLIBS)

$(OBJS): $(HEADERS) $(SOURCES)

clean:
	$(RM) $(TARGET) $(OBJS)
