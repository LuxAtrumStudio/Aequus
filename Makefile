export COMPILER = clang++
export COMPILER_FLAGS = -MMD -std=c++11 -w -c
CPP_FILES = $(wildcard *.cpp)
TOP_DIR = $(notdir $(CPP_FILES:.cpp=.o))
OBJ_FILES = $(wildcard */*.o)
OBJ_FILES += $(wildcard */*/*.o)
OBJ_FILES += $(wildcard */*/*/*.o)
OBJ_FILES += $(wildcard */*/*/*/*.o)
OBJ_FILES += $(wildcard */*/*/*/*/*.o)
OBJ_FILES += $(wildcard */*/*/*/*/*/*.o)
LINKER_FLAGS = -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer -lpessum
PROGRAM_NAME = aequus

all: $(TOP_DIR) subsystem $(PROGRAM_NAME)
	@setterm -fore green
	@printf "==========>Successfuly compiled $(PROGRAM_NAME)<==========\n"
	@setterm -fore white

$(PROGRAM_NAME): $(TOP_DIR) $(OBJ_FILES)
	@setterm -fore red
	@printf "==========>CORE<==========\n"
	@setterm -fore white
	$(COMPILER) $(TOP_DIR) $(OBJ_FILES) -o $(PROGRAM_NAME) $(LINKER_FLAGS)

%.o: %.cpp
	$(COMPILER) $(COMPILER_FLAGS) -o $(notdir $*).o $*.cpp

.PHONY : subsystem
subsystem:
	@cd aequus_files && $(MAKE)

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
	rm -f */*/*/*/*.o
	rm -f */*/*/*/*.d
	rm -f */*/*/*/*/*.o
	rm -f */*/*/*/*/*.d
	clear
	@echo Cleared all '.o' and '.d' files

.PHONY : tar
tar: clean
	tar -zcvf $(PROGRAM_NAME).tar.gz ../Aequus

.PHONY : lib
lib: all
	ar rcs lib$(PROGRAM_NAME).a $(TOTAL_OBJ_FILES)
	sudo cp lib$(PROGRAM_NAME).a /usr/local/lib/ -u
	sudo cp aequus.h /usr/local/include/
	sudo cp aequus_files/*.hpp /usr/local/include/aequus_files/
	#sudo cp aequus_files/audio/*.hpp /usr/local/include/aequus_files/audio/ -u
	sudo cp aequus_files/framework/*.hpp /usr/local/include/aequus_files/framework/ -u
	sudo cp aequus_files/input/*.hpp /usr/local/include/aequus_files/input/ -u
	sudo cp aequus_files/video/*.hpp /usr/local/include/aequus_files/video/ -u
	sudo cp aequus_files/video/object/*.hpp /usr/local/include/aequus_files/video/object/ -u
	sudo cp aequus_files/video/window/*.hpp /usr/local/include/aequus_files/video/window/ -u
	sudo cp aequus_files/video/renderer/*.hpp /usr/local/include/aequus_files/video/renderer/ -u
	sudo cp aequus_files/video/object/button/*.hpp /usr/local/include/aequus_files/video/object/button/ -u
	sudo cp aequus_files/video/object/image/*.hpp /usr/local/include/aequus_files/video/object/image/ -u
	sudo cp aequus_files/video/object/text/*.hpp /usr/local/include/aequus_files/video/object/text/ -u
	@echo Compiled lib file, and copied to usr/local/lib

.PHONY : log
log:
	less output.log

.PHONY : help
help:
	@printf "make\nmake clean\nmake tar\nmake lib\nmake log\nmake new\n"


.PHONY : new
new: clean all
