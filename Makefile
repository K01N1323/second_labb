CXX = clang++
CXXFLAGS = -std=c++17 -Wall

SRCDIR = second_labb.xcodeproj
SRCS = $(wildcard $(SRCDIR)/*.cpp)
TARGET = main

all: $(TARGET)

$(TARGET):
	$(CXX) $(CXXFLAGS) $(SRCS) -o $(TARGET)

clean:
	rm -f $(TARGET)
