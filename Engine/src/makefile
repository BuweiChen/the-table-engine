CXX = g++
CXXFLAGS = -std=c++17 -I../include -I../src -Wall -Wextra
TARGET = ../bin/game
SRCS = app.cpp gameapp.cpp gameobject.cpp component.cpp script.cpp
OBJS = $(SRCS:%.cpp=../bin/%.o)
LDFLAGS = -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) -o $@ $^ $(LDFLAGS)

../bin/%.o: %.cpp | bin
	$(CXX) $(CXXFLAGS) -c $< -o $@

bin:
	mkdir -p ../bin

clean:
	rm -rf ../bin 