CXX = clang++
CXXFLAGS = -std=c++17 -Wall

SRCDIR = second_labb.xcodeproj
SRCS = $(SRCDIR)/main.cpp $(SRCDIR)/menu.cpp $(SRCDIR)/tests.cpp
OBJS = $(SRCS:.cpp=.o)
TARGET = main

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(TARGET)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(TARGET) $(OBJS)
