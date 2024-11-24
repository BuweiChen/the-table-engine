CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra
TARGET = game
SRCS = app.cpp
OBJS = $(SRCS:.cpp=.o)
LDFLAGS = -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) -o $@ $^ $(LDFLAGS)

clean:
	rm -f $(TARGET) $(OBJS)
