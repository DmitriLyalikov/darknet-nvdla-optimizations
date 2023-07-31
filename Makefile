# Compiler and compiler flags for RISC-V
CC := riscv64-unknown-elf-gcc
CFLAGS := -march=rv64imafdc -mabi=lp64d -mcmodel=medlow -O3 -std=c99

# Source files
SRC := main.c converter.c converter_layer.c

# Object files
OBJ := $(SRC:.c=.o)

# Output executable name
TARGET := my_program

# Rule to compile .c files to .o files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Main rule to build the executable
$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(TARGET)

# Clean rule to remove object files and the executable
clean:
	rm -f $(OBJ) $(TARGET)
