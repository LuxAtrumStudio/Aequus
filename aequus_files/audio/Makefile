CPP_FILES = $(wildcard *.cpp)
OBJ_FILES = $(notdir $(CPP_FILES:.cpp=.o))
CC = g++
COMPILER_FLAGS = -MMD -std=c++11 -w -c
LINKER_FLAGS = -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer
main:$(OBJ_FILES)
%.o: %.cpp %.h
	g++ $(COMPILER_FLAGS) -o $(notdir $*).o $*.cpp $(LINKER_FLAGS)
