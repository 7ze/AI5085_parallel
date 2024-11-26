# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -pedantic -std=c99 -g -O2 -I$(INC_DIR) -fopenmp
LDFLAGS = -fopenmp

# Directories
SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = bin
INC_DIR = include

# Files
SRC_FILES = $(wildcard $(SRC_DIR)/*.c)  # Automatically find all .c files in src/
OBJ_FILES = $(SRC_FILES:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
EXEC = $(BIN_DIR)/sort

# Targets
all: $(EXEC)

# Rule for creating the final executable
$(EXEC): $(OBJ_FILES)
	mkdir -p $(BIN_DIR)  # Ensure bin directory exists
	$(CC) $(OBJ_FILES) -o $(EXEC) $(LDFLAGS)

# Rule for creating object files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	mkdir -p $(OBJ_DIR)  # Ensure obj directory exists
	$(CC) $(CFLAGS) -c $< -o $@

# Clean up object files and executable
clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)
