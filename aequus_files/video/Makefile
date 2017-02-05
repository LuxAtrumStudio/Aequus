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
	@printf "OBJECT\n"
	@setterm -fore white
	@cd object && $(MAKE)
	@setterm -fore cyan
	@printf "VIDEO/"
	@setterm -fore green
	@printf "RENDERER\n"
	@setterm -fore white
	@cd renderer && $(MAKE)
	@setterm -fore cyan
	@printf "VIDEO/"
	@setterm -fore cyan
	@printf "WINDOW\n"
	@setterm -fore white
	@cd window && $(MAKE)
	@setterm -fore cyan
	@printf "VIDEO/"
	@setterm -fore red
	@printf "LAYOUT\n"
	@setterm -fore white
	@cd layout && $(MAKE)
