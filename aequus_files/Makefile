CPP_FILES = $(wildcard *.cpp)
OBJ_FILES = $(notdir $(CPP_FILES:.cpp=.o))

all: $(OBJ_FILES) subsystem

%.o: %.cpp %.hpp
	@printf "Compiling $*.cpp...\n"
	@$(COMPILER) $(FLAGS) -o $(notdir $*).o $*.cpp

.PHONY : subsystem
subsystem:
	@setterm -fore green; printf "Input\n"; setterm -fore white
	@cd input && $(MAKE)
	@setterm -fore magenta; printf "Object\n"; setterm -fore white
	@cd object && $(MAKE)
	@setterm -fore blue; printf "Window\n"; setterm -fore white
	@cd window && $(MAKE)
