CC=gcc
CCFLAGS=-std=c17 -Wall -Wextra
TARGET=cirrus

SRC=src/main.c \
	src/flag/flag.c \
	src/flag/help.c \
	src/error/error.c
OBJ=$(SRC:.c=.o)

$(TARGET): $(OBJ)
	$(CC) $(CCFLAGS) -o $(TARGET) $(OBJ)

%.o: %.cpp
	$(CC) $(CCFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(TARGET)