# Compiler
CC = gcc
OUT = snake_game

# Directories
SRC_DIR = src
LIB_DIR = lib

# Flags for warnings and include directories
CFLAGS = -Wall -Wextra -std=c99 -I$(LIB_DIR)
LDFLAGS = -lncurses

# Source files
SRC = $(SRC_DIR)/snake.c $(SRC_DIR)/main.c $(SRC_DIR)/interface.c

# Object files created at build
OBJ = $(SRC:.c=.o)

# Build program
build: $(OBJ)
	$(CC) $(OBJ) -o $(OUT) $(LDFLAGS)

# Compile each source file separately
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Run
run: build
	./$(OUT)

# Clean
clean:
	rm -f $(OBJ) $(OUT)

# Pack
pack:
	zip -FSr file.zip README Makefile $(SRC) $(LIB_DIR)/*.h

.PHONY: pack clean

