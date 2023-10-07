# Copyright 2022-2023 Stoica Bogdan (bogdanstoicasn@yahoo.com)
# Compiler
CC = gcc
OUT = test

# Flags for warnings
CFLAGS = -Wall -Wextra -std=c99
LDFLAGS = -lncurses

# Object files created at build
OBJ = interface.o main.o

# Build program
build: $(OBJ)
	$(CC) $(OBJ) -o $(OUT) $(LDFLAGS)

# Interface compilation
interface: interface.c
	$(CC) $(CFLAGS) -c interface.c $(LDFLAGS)

# Main compilation
main: main.c
	$(CC) $(CFLAGS) -c main.c

# Run
run: build
	./$(OUT)

# Clean
clean:
	rm -f *.o $(OUT)

# Pack
pack:
	zip -FSr file.zip README Makefile *.c *.h

.PHONY: pack clean
