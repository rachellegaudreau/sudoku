# Compiler
CXX = g++
CXXFLAGS = -Wall -std=c++17

# Executable name
TARGET = sudoku

# Source files
SRCS = main.cpp board.cpp move.cpp

# Object files (replacing .cpp with .o)
OBJS = $(SRCS:.cpp=.o)

# Build target
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

# Compile .cpp to .o
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean compiled files
clean:
	rm -f $(OBJS) $(TARGET)
