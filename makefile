# Name of the executable
EXECUTABLE := tetris
DBG_EXECUTABLE := $(EXECUTABLE)_debug

# Main directories
BIN_DIR := ./bin
BUILD_DIR := ./build
BUILD_DBG_DIR := ./debug_build
SRC_DIR := ./src

# Find all the cpp files under the source directory
SRCS := $(shell find $(SRC_DIR) -name *.cpp)

# Get all the object files for each of the source files found.
OBJS := $(SRCS:$(SRC_DIR)/%.cpp=$(BUILD_DIR)/%.o)
DBG_OBJS := $(SRCS:$(SRC_DIR)/%.cpp=$(BUILD_DBG_DIR)/%.o)

# Dependencies
DEPS := $(OBJS:.o=.d)
DBG_DEPS := $(DBG_OBJS:.o=.d)

# Compiler Settings
CC := g++
LINKER_FLAGS := -lSDL2 -lSDL2_image -lSDL2_mixer -lSDL2_ttf
INCLUDE_FLAGS := #-Iinclude
COMPILER_FLAGS := -Wall -Wextra -Wshadow -Wpedantic -x c++ -std=c++17 -MMD -MP $(LINKER_FLAGS)
RELEASE_FLAGS := -O3
DEBUG_FLAGS := -g -O0

# This is the main program target
$(BIN_DIR)/$(EXECUTABLE): $(OBJS)
	@mkdir -p  $(BIN_DIR)
	$(CC) $(OBJS) $(COMPILER_FLAGS) $(RELEASE_FLAGS) -o $@
	@compiledb -n make

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(BUILD_DIR)
	$(CC) -c $(COMPILER_FLAGS) $(RELEASE_FLAGS) $< -o $@

json_compilation:
	compiledb -n make

# This is the debug Build
debug: $(BIN_DIR)/$(DBG_EXECUTABLE)

$(BIN_DIR)/$(DBG_EXECUTABLE): $(DBG_OBJS)
	@mkdir -p  $(BIN_DIR)
	$(CC) $(DBG_OBJS) $(COMPILER_FLAGS) $(DEBUG_FLAGS) -o $@
	@compiledb -n make

$(BUILD_DBG_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(BUILD_DBG_DIR)
	$(CC) -c $(COMPILER_FLAGS) $(DEBUG_FLAGS) $< -o $@

.PHONY: clean
clean:
	rm ./compile_commands.json
	rm -r $(BIN_DIR)
	rm -r $(BUILD_DIR)
	rm -r $(BUILD_DBG_DIR)

-include $(DEPS)
-include $(DBG_DEPS)
