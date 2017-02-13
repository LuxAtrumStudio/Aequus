CPP_FILES = $(wildcard *.cpp)
OBJ_FILES = $(notdir $(CPP_FILES:.cpp=.o))

all: $(OBJ_FILES) subsystem

%.o: %.cpp %.hpp
	$(COMPILER) $(COMPILER_FLAGS) -o $(notdir $*).o $*.cpp

.PHONY : subsystem
subsystem:
	@setterm -fore cyan
	@printf "VIDEO/"
	@setterm -fore blue
	@printf "OBJECT/"
	@setterm -fore yellow
	@printf "GRAPH/"
	@setterm -fore blue
	@printf "PLOT\n"
	@setterm -fore white
	@cd plot && $(MAKE)
