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
	@setterm -fore blue
	@printf "IMAGE\n"
	@setterm -fore white
	@cd image && $(MAKE)
	@setterm -fore cyan
	@printf "VIDEO/"
	@setterm -fore blue
	@printf "OBJECT/"
	@setterm -fore green
	@printf "TEXT\n"
	@setterm -fore white
	@cd text && $(MAKE)
	@setterm -fore cyan
	@printf "VIDEO/"
	@setterm -fore blue
	@printf "OBJECT/"
	@setterm -fore cyan
	@printf "BUTTON\n"
	@setterm -fore white
	@cd button && $(MAKE)
	@setterm -fore cyan
	@printf "VIDEO/"
	@setterm -fore blue
	@printf "OBJECT/"
	@setterm -fore red
	@printf "SPACER\n"
	@setterm -fore white
	@cd spacer && $(MAKE)
	@setterm -fore cyan
	@printf "VIDEO/"
	@setterm -fore blue
	@printf "OBJECT/"
	@setterm -fore magenta
	@printf "CANVAS\n"
	@setterm -fore white
	@cd canvas && $(MAKE)
