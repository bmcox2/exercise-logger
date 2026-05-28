CXX = g++
CXXFLAGS = -Wall -g -std=c++17 -I include -I .
TARGET = logger
SRCS = $(wildcard src/*.cpp)
OBJS = $(SRCS:src/%.cpp=%.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(TARGET)

%.o: src/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f *.o *.exe $(TARGET)