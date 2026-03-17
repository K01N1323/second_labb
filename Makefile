CXX = clang++
CXXFLAGS = -std=c++17 -Wall

SRCDIR = second_labb.xcodeproj
SRCS = $(SRCDIR)/main.cpp $(SRCDIR)/menu.cpp $(SRCDIR)/tests.cpp
OBJS = $(SRCS:.cpp=.o)
HDRS = $(wildcard $(SRCDIR)/*.h)
TARGET = main

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(TARGET)

$(SRCDIR)/%.o: $(SRCDIR)/%.cpp $(HDRS)
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(TARGET) $(OBJS)
