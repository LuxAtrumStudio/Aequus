CPP_FILES = $(wildcard *.cpp)
OBJ_FILES = $(notdir $(CPP_FILES:.cpp=.o))

all: subsystem $(OBJ_FILES)

%.o: %.cpp %.hpp
	$(COMPILER) $(COMPILER_FLAGS) -o $(notdir $*).o $*.cpp

.PHONY : subsystem
subsystem:
	@setterm -fore red
	@printf "AUDIO/"
	@setterm -fore blue
	@printf "CHUNK\n"
	@setterm -fore white
	@cd chunk && $(MAKE)
	@setterm -fore red
	@printf "AUDIO/"
	@setterm -fore green
	@printf "MUSIC\n"
	@setterm -fore white
	@cd music && $(MAKE)
