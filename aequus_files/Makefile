CPP_FILES = $(wildcard *.cpp)
OBJ_FILES = $(notdir $(CPP_FILES:.cpp=.o))

all: $(OBJ_FILES) subsystem

%.o: %.cpp %.hpp
	@printf "Compiling $*.cpp...\n"
	@$(COMPILER) $(FLAGS) -o $(notdir $*).o $*.cpp

.PHONY : subsystem
subsystem:
	@setterm -fore green; printf "$(shell pwd)/input:\n"; setterm -fore white
	@cd input && $(MAKE)
	@setterm -fore green; printf "$(shell pwd)/object:\n"; setterm -fore white
	@cd object && $(MAKE)
	@setterm -fore green; printf "$(shell pwd)/sld_extention:\n"; setterm -fore white
	@cd sdl_extention && $(MAKE)
	@setterm -fore green; printf "$(shell pwd)/types:\n"; setterm -fore white
	@cd types && $(MAKE)
	@setterm -fore green; printf "$(shell pwd)/window:\n"; setterm -fore white
	@cd window && $(MAKE)
