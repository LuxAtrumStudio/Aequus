CPP_FILES = $(wildcard *.cpp)
OBJ_FILES = $(notdir $(CPP_FILES:.cpp=.o))

all: $(OBJ_FILES) subsystem

%.o: %.cpp %.hpp
	$(COMPILER) $(COMPILER_FLAGS) -o $(notdir $*).o $*.cpp

.PHONY : subsystem
subsystem:
	@setterm -fore blue
	@printf "FRAMEWORK\n"
	@setterm -fore white
	@cd framework && $(MAKE)
	@setterm -fore green
	@printf "INPUT\n"
	@setterm -fore white
	@cd input && $(MAKE)
	@setterm -fore cyan
	@printf "VIDEO\n"
	@setterm -fore white
	@cd video && $(MAKE)
