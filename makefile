# Name of the executable
EXECUTABLE := my_program

# Main directories
BIN_DIR := ./bin
BUILD_DIR := ./build
SRC_DIR := ./src

# File specifying the flags for proper autocompletion
FLAG_FILE := ./.clang

# Find all the cpp files under the source directory
SRCS := $(shell find $(SRC_DIR) -name *.cpp)

# Get all the object files for each of the source files found.
OBJS := $(SRCS:$(SRC_DIR)/%.cpp=$(BUILD_DIR)/%.o)

# Compiler Settings
CC := g++
LINKER_FLAGS := -lSDL2_image -lSDL2
INCLUDE_FLAGS := #-Iinclude
COMPILER_FLAGS := -Wall -Wextra -Wshadow -Wpedantic -x c++ -std=c++17 $(LINKER_FLAGS) $(INCLUDE_FLAGS)

#This is the main program target
$(BIN_DIR)/$(EXECUTABLE): $(OBJS)
	mkdir -p  $(BIN_DIR)
	$(CC) $(OBJS) $(COMPILER_FLAGS) -o $@
	compiledb make

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	mkdir -p $(BUILD_DIR)
	$(CC) -c $(COMPILER_FLAGS) $< -o $@

json_compilation:
	compiledb make


.PHONY: clean
clean:
	rm ./compile_commands.json
	rm -r $(BIN_DIR)
	rm -r $(BUILD_DIR)
