# Define the compiler and the flags
CXX = g++
CXXFLAGS = -Wall -std=c++11

# Define the target executable
TARGET = m

# Define the source and header files for the main program
MAIN_SRCS = main.cpp player.cpp board.cpp hexagon.cpp edge.cpp vertex.cpp catan.cpp
HDRS = player.hpp board.hpp catan.hpp

# Define the source files for the tests
TEST_SRCS = test.cpp doctest_main.cpp

# Define the object files
MAIN_OBJS = $(MAIN_SRCS:.cpp=.o)
TEST_OBJS = $(filter-out main.o, $(MAIN_OBJS)) $(TEST_SRCS:.cpp=.o)

# Rule to build the main executable
$(TARGET): $(MAIN_OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(MAIN_OBJS)

# Rule to build the test executable
test: $(TEST_OBJS)
	$(CXX) $(CXXFLAGS) -o test $(TEST_OBJS)

# Rule to build the object files
%.o: %.cpp $(HDRS)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean up the build files
clean:
	rm -f $(MAIN_OBJS) $(TEST_OBJS) $(TARGET) test

# Phony targets
.PHONY: clean test
