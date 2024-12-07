CXX = g++
CXXFLAGS = -std=c++17 -I../include -I../src -Wall -Wextra -fPIC
TARGET = ../bin/game
LIB_TARGET = ../lib/libengine.a
SRCS = $(wildcard *.cpp components/*.cpp)
GAME_OBJS = $(SRCS:%.cpp=../bin/obj/%.o)
LIB_OBJS = $(SRCS:%.cpp=../bin/obj/lib/%.o)

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
        CXXFLAGS += -I../lib
    else ifeq ($(UNAME_M), x86_64)
        # macOS x86
        LDFLAGS += -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer
    endif
endif

all: $(TARGET) $(LIB_TARGET)

$(TARGET): $(GAME_OBJS)
	$(CXX) -o $@ $^ $(LDFLAGS)

$(LIB_TARGET): $(LIB_OBJS)
	mkdir -p ../lib
	ar rcs $@ $^

../bin/obj/%.o: %.cpp | bin
	$(CXX) $(CXXFLAGS) -c $< -o $@

../bin/obj/lib/%.o: %.cpp | bin_lib
	$(CXX) $(CXXFLAGS) -fPIC -c $< -o $@

bin:
	mkdir -p ../bin/obj
	mkdir -p ../bin/obj/components

bin_lib:
	mkdir -p ../bin/obj/lib
	mkdir -p ../bin/obj/lib/components

run: $(TARGET)
	./$(TARGET)

clean:
	rm -rf ../bin/obj
	rm -f ../bin/game
	rm -f ../lib/libengine.a

.PHONY: all clean run