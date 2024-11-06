# Compiler and flags
CC = gcc
CFLAGS = -Wall -g -o2 -fopenmp

# Source files and build directory
SRCDIR = .
BUILDDIR = build
SRC = $(wildcard $(SRCDIR)/*.c)
OBJ = $(patsubst $(SRCDIR)/%.c, $(BUILDDIR)/%, $(SRC))

# Default target
all: $(OBJ)

# Compile each .c file to its own executable in the build directory
$(BUILDDIR)/%: $(SRCDIR)/%.c | $(BUILDDIR)
	$(CC) $(CFLAGS) $< -o $@

# Create the build directory if it doesn't exist
$(BUILDDIR):
	mkdir -p $(BUILDDIR)

# Clean up build directory
clean:
	rm -rf $(BUILDDIR)
