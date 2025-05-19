# Define the compiler and the flags constants
CC = gcc
CFLAGS = -Wall

# Define the target executable
TARGET = netFlow

# Define the object files
OBJ = router_lib.o router_main.o

# Define the output file
OUTPUT = output.txt

# Build the target
$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(TARGET)

# Explicit rule to create object files from .c files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Creates a cleanup routine to remove object and target files
clean:
	rm -f $(OBJ) $(TARGET) $(OUTPUT)

# Creates a run routine to run your program
run: $(TARGET)
	./$(TARGET) > $(OUTPUT)
#	./$(TARGET)