CC=gcc
CCFLAGS=-std=c17 -Wall -Wextra 
TARGET=cirrus

SRC=src/main.c \
	src/flag/flag.c \
	src/error/error.c \
	src/flag/flags/help.c \
	src/flag/flags/build.c \
	src/lexer/tokenize.c \
	src/lexer/free.c \
	src/file/file.c \
	src/ast/parser.c \
	src/ast/free.c
OBJ=$(SRC:.c=.o)

$(TARGET): $(OBJ)
	$(CC) $(CCFLAGS) -o $(TARGET) $(OBJ)
	rm -f $(OBJ)

%.o: %.c
	$(CC) $(CCFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(TARGET)