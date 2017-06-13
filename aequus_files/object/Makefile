CPP_FILES = $(wildcard *.cpp)
OBJ_FILES = $(notdir $(CPP_FILES:.cpp=.o))

all: $(OBJ_FILES) subsystem

%.o: %.cpp %.hpp
	@printf "Compiling $*.cpp...\n"
	@$(COMPILER) $(FLAGS) -o $(notdir $*).o $*.cpp

.PHONY : subsystem
subsystem:
	@setterm -fore blue; printf "$(shell pwd)/geometry:\n"; setterm -fore white
	cd geometry && $(MAKE)
	@setterm -fore blue; printf "$(shell pwd)/image:\n"; setterm -fore white
	@cd image && $(MAKE)
	@setterm -fore blue; printf "$(shell pwd)/layout:\n"; setterm -fore white
	@cd layout && $(MAKE)
