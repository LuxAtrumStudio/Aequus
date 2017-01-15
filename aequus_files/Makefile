CPP_FILES = $(wildcard *.cpp)
OBJ_FILES = $(notdir $(CPP_FILES:.cpp=.o))
COMPILER_FLAGS = -MMD -std=c++11 -w -c
LINKER_FLAGS = -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer

all: subsystem main

.PHONY : main
main:$(OBJ_FILES)
%.o: %.cpp %.h
	$(CC) $(COMPILER_FLAGS) -o $(notdir $*).o $*.cpp $(LINKER_FLAGS)

.PHONY : subsystem
subsystem:
	setterm -foreground green
	@echo =====-----AUDIO FILES:
	cd audio && $(MAKE)
	setterm -foreground cyan
	@echo =====-----FRAMEWORK FILES:
	cd framework && $(MAKE)
	setterm -foreground red
	@echo =====-----INPUT FILES:
	cd input && $(MAKE)
	setterm -foreground magenta
	@echo =====-----VIDEO FILES:
	cd video && $(MAKE)
	setterm -foreground yellow
	@echo =====----------OBJECT FILES:
	cd video/object && $(MAKE)
	setterm -foreground blue
