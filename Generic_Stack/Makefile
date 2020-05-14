CC=gcc

CFLAGS += -I../include
CFLAGS += -g3 -ansi -pedantic -Wall -Werror -Wextra

TARGET =stack_test
SOURCES ?= $(wildcard *.c)
OBJECTS ?= $(SOURCES:.c=.o)

all: $(TARGET) run

$(TARGET) : $(OBJECTS)

include depends
depends:
	$(CC) -MM $(CFLAGS) $(SOURCES) > depends

clean:
	rm -f $(TARGET) *.o *.gch depends

run: $(TARGET)
	./$(TARGET) -v

