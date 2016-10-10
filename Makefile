CPP_FILES = $(wildcard *.cpp)
OBJ_FILES = $(notdir $(CPP_FILES:.cpp=.o))
TOTAL_OBJ_FILES = $(OBJ_FILES) $(wildcard */*.o) $(wildcard */*/*.o) $(wildcard */*/*/*.o)
CC = g++
COMPILER_FLAGS = -MMD -std=c++11 -w -c
LINKER_FLAGS = -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer
PROGRAM_NAME = aequus

all: subsystem top_obj $(PROGRAM_NAME)
	clear
	@echo Compleated compiling $(PROGRAM_NAME)

$(PROGRAM_NAME): $(OBJ_FILES) $(wildcard */*.o) $(wildcard */*/*.o) $(wildcard */*/*/*.o)
	setterm -foreground red
	$(CC) $(TOTAL_OBJ_FILES) -o $(PROGRAM_NAME) $(LINKER_FLAGS)
	setterm -default

%.o: %.cpp
	g++ $(COMPILER_FLAGS) -o $(notdir $*).o $*.cpp

.PHONY : top_obj
top_obj:$(OBJ_FILES)

.PHONY : subsystem
subsystem:
	setterm -background white -foreground black
	cd pessum_files && $(MAKE)
	setterm -background black -foreground blue
	cd aequus_files && $(MAKE)
	setterm -default

.PHONY : clean
clean:
	rm -f *.o
	rm -f *.d
	rm -f */*.o
	rm -f */*.d
	rm -f */*/*.o
	rm -f */*/*.d
	rm -f */*/*/*.o
	rm -f */*/*/*.d
	clear
	@echo Cleared all '.o' and '.d' files

.PHONY : run
run:
	./aequus

.PHONY : compress
compress:
	cd ../
	tar -zcvf $(PROGRAM_NAME).tar.gz Aequus