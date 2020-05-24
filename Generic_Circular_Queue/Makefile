CC=gcc

CFLAGS += -I../include
CFLAGS += -g3 -ansi -pedantic -Wall -Werror -Wextra

TARGET = generic_circular_queue_test
SOURCES ?= $(wildcard *.c)
OBJECTS ?= $(SOURCES:.c=.o)

all: $(TARGET) run

$(TARGET) : $(OBJECTS)

clean:
	rm -f $(TARGET) *.o *.gch depends

run: $(TARGET)
	./$(TARGET) -v

