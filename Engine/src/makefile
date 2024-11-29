CXX = g++
CXXFLAGS = -std=c++17 -I../include -I../src -Wall -Wextra
TARGET = ../bin/game
SRCS = $(wildcard *.cpp components/*.cpp)
OBJS = $(SRCS:%.cpp=../bin/%.o)
LDFLAGS = -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) -o $@ $^ $(LDFLAGS)

../bin/%.o: %.cpp | bin
	$(CXX) $(CXXFLAGS) -c $< -o $@

bin:
	mkdir -p ../bin
	mkdir -p ../bin/components

run: $(TARGET)
	./$(TARGET)

clean:
	rm -rf ../bin 