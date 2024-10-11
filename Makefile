# Define the compiler
CC = gcc

# Define the source file
SRC = main.c

# Define the output file
OUT = tema1

# Build and run target
build_and_run: $(SRC)
	$(CC) $(SRC) -o $(OUT)
	./$(OUT)

# Clean target
clean:
	rm -f $(OUT)
