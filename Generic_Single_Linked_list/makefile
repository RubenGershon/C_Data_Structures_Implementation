#make file to Generic Vector

CC=gcc
CFLAGS += -g3 -ansi -pedantic -Wall -Werror -Wextra

TARGET = generic_single_linked_list_test
SOURCES ?= $(wildcard *.c)
OBJECTS ?= $(SOURCES:.c=.o)

all: $(TARGET) run

$(TARGET) : $(OBJECTS)

clean:
	rm -f $(TARGET) *.o *.gch depends

run: $(TARGET)
	./$(TARGET) -v
