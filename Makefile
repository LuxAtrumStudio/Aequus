CPP_FILES = $(wildcard *.cpp)
OBJ_FILES = $(notdir $(CPP_FILES:.cpp=.o))
TOTAL_OBJ_FILES = $(wildcard */*.o) $(wildcard */*/*.o) $(wildcard */*/*/*.o)
HEADER_FILES = $(wildcard *.h) $(wildcard */*.h) $(wildcard */*/*.h) $(wildcard */*/*/*.h)
CC = clang++
COMPILER_FLAGS = -MMD -std=c++11 -w -c
LINKER_FLAGS = -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer -lpessum
PROGRAM_NAME = aequus

all: subsystem top_obj $(PROGRAM_NAME)
	clear
	@echo Compleated compiling $(PROGRAM_NAME)

$(PROGRAM_NAME): $(OBJ_FILES) $(wildcard */*.o) $(wildcard */*/*.o) $(wildcard */*/*/*.o)
	setterm -foreground red
	$(CC) $(OBJ_FILES) $(TOTAL_OBJ_FILES) -o $(PROGRAM_NAME) $(LINKER_FLAGS)
	setterm -default

%.o: %.cpp
	$(CC) $(COMPILER_FLAGS) -o $(notdir $*).o $*.cpp

.PHONY : top_obj
top_obj:$(OBJ_FILES)

.PHONY : subsystem
subsystem:
	export CC
	setterm -foreground blue
	@echo =====AEQUUS FILES:
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

.PHONY : test
test: subsystem top_obj $(PROGRAM_NAME)
	./aequus

.PHONY : tar
tar: clean
	tar -zcvf $(PROGRAM_NAME).tar.gz ../Aequus

.PHONY : lib
lib: all
	ar rcs lib$(PROGRAM_NAME).a $(TOTAL_OBJ_FILES)
	sudo cp lib$(PROGRAM_NAME).a /usr/local/lib/ -u
	sudo cp aequus.h /usr/local/include/
	sudo cp aequus_files/*.h /usr/local/include/aequus_files/
	sudo cp aequus_files/audio/*.h /usr/local/include/aequus_files/audio/ -u
	sudo cp aequus_files/framework/*.h /usr/local/include/aequus_files/framework/ -u
	sudo cp aequus_files/input/*.h /usr/local/include/aequus_files/input/ -u
	sudo cp aequus_files/video/*.h /usr/local/include/aequus_files/video/ -u
	sudo cp aequus_files/video/object/*.h /usr/local/include/aequus_files/video/object/ -u
	clear
	@echo Compiled lib file, and copied to usr/local/lib

.PHONY : log
log:
	less output.log

.PHONY : help
help:
	@echo make clean
	@echo make test
	@echo make tar
	@echo make lib
	@echo make log
	@echo make new


.PHONY : new
new: clean all
