# Compiler
CC = g++

# Compiler flags
CFLAGS = -std=c++11 -Wall -g 

# Executable output file
OUTPUT = vfs

# Source file
SRC = main.cpp

all: $(OUTPUT)

$(OUTPUT): $(SRC)
	$(CC) $(CFLAGS) $(SRC) -o $(OUTPUT)

clean:
	rm -f $(OUTPUT)
