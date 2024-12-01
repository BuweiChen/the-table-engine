CXX = g++
CXXFLAGS = -std=c++17 -I../include -I../src -Wall -Wextra
TARGET = ../bin/game
SRCS = $(wildcard *.cpp components/*.cpp)
OBJS = $(SRCS:%.cpp=../bin/obj/%.o)
LDFLAGS = -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) -o $@ $^ $(LDFLAGS)

../bin/obj/%.o: %.cpp | bin
	$(CXX) $(CXXFLAGS) -c $< -o $@

bin:
	mkdir -p ../bin/obj
	mkdir -p ../bin/obj/components

run: $(TARGET)
	./$(TARGET)

clean:
	rm -rf ../bin 