# Compiler and flags
CXX = g++
CXXFLAGS = -g -std=c++11 -O2
LDLIBS = -lncursesw

# Target executable
TARGET = nim_game

# Source files
SRC = nim.cpp start.cpp

# Header files
HEADERS = nim.h display.h

# Other dependencies (if your program reads these at runtime, they don't need to be listed here)
DEPS = structure.txt Alphabet.txt

# Default rule
all: $(TARGET)

# Linking rule
$(TARGET): $(SRC) $(HEADERS)
	$(CXX) $(CXXFLAGS) $(SRC) -o $(TARGET) $(LDLIBS)

# Run the game
run: all
	./$(TARGET)

# Clean rule (removes the executable)
clean:
	rm -f $(TARGET)


