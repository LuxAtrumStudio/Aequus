CPP_FILES = $(wildcard *.cpp)
OBJ_FILES = $(notdir $(CPP_FILES:.cpp=.o))
CC = g++
COMPILER_FLAGS = -MMD -std=c++11 -w -c
LINKER_FLAGS = -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer

all: subsystem main

.PHONY : main
main:$(OBJ_FILES)
%.o: %.cpp %.h
	g++ $(COMPILER_FLAGS) -o $(notdir $*).o $*.cpp $(LINKER_FLAGS)

.PHONY : subsystem
subsystem:
	cd audio && $(MAKE)
	cd framework && $(MAKE)
	cd input && $(MAKE)
	cd video && $(MAKE)
	cd video/object && $(MAKE)
