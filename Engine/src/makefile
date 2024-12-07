CXX = g++
CXXFLAGS = -std=c++17 -I../include -I../src -I../lib -Wall -Wextra
TARGET = ../bin/game
SRCS = $(wildcard *.cpp components/*.cpp)
OBJS = $(SRCS:%.cpp=../bin/obj/%.o)

# Configure LDFLAGS based on platform
UNAME_S := $(shell uname -s)
UNAME_M := $(shell uname -m)

ifeq ($(UNAME_S), Linux)
    ifneq ($(findstring WSL,$(shell uname -r)),)
        # WSL
        LDFLAGS += -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer
    else
        # Native Linux
        LDFLAGS += -lSDL2 -lSDL2_ttf
    endif
else ifeq ($(UNAME_S), Darwin)
    ifeq ($(UNAME_M), arm64)
        # macOS ARM (M1/M2)
        LDFLAGS += -rpath /Library/Frameworks -F/Library/Frameworks -framework SDL2 -framework SDL2_ttf
    else ifeq ($(UNAME_M), x86_64)
        # macOS x86
        LDFLAGS += -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer
    endif
endif

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