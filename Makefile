# Makefile
# Compiler
CXX := clang++
CXXFLAGS := -std=c++20 -Wall -Wextra -O2

# Paths
SRC_DIR := src
BIN_DIR := bin
TARGET := $(BIN_DIR)/day_one

# Source files
SRCS := $(SRC_DIR)/day_one.cc

# Default rule
all: $(TARGET)

# Create bin directory if missing
$(BIN_DIR):
	mkdir -p $(BIN_DIR)

# Build target
$(TARGET): $(SRCS) | $(BIN_DIR)
	$(CXX) $(CXXFLAGS) $(SRCS) -o $(TARGET)

# Run the program with input file
run: $(TARGET)
	./$(TARGET)

# Clean up
clean:
	rm -rf $(BIN_DIR)

.PHONY: all run clean
