CC = gcc
CFLAGS = -Iinclude -Wall -Wextra -std=c11

SRC = src/main.c src/calculator.c
OBJ = $(SRC:.c=.o)

TARGET = app
LIB = libcalc.a

all: $(LIB) $(TARGET)

$(LIB): src/calculator.o
	ar rcs $(LIB) src/calculator.o

$(TARGET): src/main.o $(LIB)
	$(CC) -o $(TARGET) src/main.o -L. -lcalc

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f src/*.o $(TARGET) $(LIB)

.PHONY: all clean

