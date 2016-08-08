CPP_FILES = $(wildcard *.cpp)
OBJ_FILES = $(notdir $(CPP_FILES:.cpp=.o))
TOTAL_OBJ_FILES = $(OBJ_FILES) $(wildcard */*.o)
CC = g++
COMPILER_FLAGS = -MMD -std=c++11 -w -c
LINKER_FLAGS = -lSDL2
PROGRAM_NAME = aequustest

all: subsystem top_obj $(PROGRAM_NAME)
	clear
	@echo Compleated compiling $(PROGRAM_NAME)

$(PROGRAM_NAME): $(TOTAL_OBJ_FILES)
	$(CC) $(LINKER_FLAGS) $(TOTAL_OBJ_FILES) -o $(PROGRAM_NAME)

%.o: %.cpp
	g++ $(COMPILER_FLAGS) -o $(notdir $*).o $*.cpp

.PHONY : top_obj
top_obj:$(OBJ_FILES)

.PHONY : subsystem
subsystem:
	cd Pessum && $(MAKE)
	cd Aequus && $(MAKE)

.PHONY : clean
clean:
	rm -f *.o
	rm -f *.d
	rm -f */*.o
	rm -f */*.d
	clear
	@echo Cleared all '.o' and '.d' files
