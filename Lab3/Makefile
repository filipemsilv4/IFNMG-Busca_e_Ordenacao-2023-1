# Compiler settings
CXX=g++
CXXFLAGS=-std=c++11
LIBS=-lncurses

# Source files
SRCS=main.cpp sort.cpp

# Object files
OBJS=$(SRCS:.cpp=.o)

# Target executable
TARGET=main

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) $(LIBS) -o $(TARGET)
	rm -f $(OBJS)

clean:
	rm -f $(OBJS) $(TARGET)