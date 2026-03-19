CXX = clang++
CXXFLAGS = -std=c++17 -Wall

SRCS = main.cpp menu.cpp tests.cpp
OBJS = $(SRCS:.cpp=.o)
HDRS = $(wildcard *.h)
TARGET = main

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(TARGET)

%.o: %.cpp $(HDRS)
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(TARGET) $(OBJS)
