SHELL = /bin/bash

export SOURCE_DIR = source
export TEST_DIR = 
export BUILD_DIR = build

export COMPILER = clang++
export CPPFLAGS = -MMD -std=c++11 -w -c
export LINK = -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer -lpessum
export NAME = aequus
export TYPE = lib

export LIB_PATH = /usr/local/
export EXE_PATH = ~/bin/

export RED = \033[0;31m
export GREEN = \033[0;32m
export YELLOW = \033[0;33m
export BLUE = \033[0;34m
export MAGENTA = \033[0;35m
export CYAN = \033[0;36m
export WHITE = \033[0;37m
export NO_COLOR = \033[m

export BUILD_COLOR = $(BLUE)
export ERR_COLOR = $(RED)
export OK_COLOR = $(GREEN)
export CLEAN_COLOR = $(YELLOW)
export INSTALL_COLOR = $(MAGENTA)

export WIDTH=$(shell printf $$(($(call FindLongestFile, $(SOURCE_DIR)) + 14)))
export BASE_PATH=$(shell pwd)

ifndef .VERBOSE
  .SILENT:
endif

define FindLongestFile
$(shell \
  max=0; \
  for file in `find $(1) -type f -exec basename {} \;`; do \
    len=$${#file}; \
    if [ $$len -gt $$max ]; then \
      max=$$len; \
    fi; \
  done; \
  echo $$max
)
endef

define Line = 
$(shell printf '%0.1s' "$(2)"{1..$(1)})
endef

define Print
var="$(1)"; \
    width="$(2)";\
    printf '%s%*.*s' "$$var" 0 $$(($$width - $${#var} - 1)) "$(call Line,$(2),.)"
endef

define check =
  printf "%b\n" "$(OK_COLOR)\xE2\x9C\x94 $(NO_COLOR)"
endef

define cross =
  printf "%b\n" "$(ERR_COLOR)\xE2\x9D\x8C $(NO_COLOR)"
endef

all: start source-make test-make 
	printf "%b%s%b\n" "$(WHITE)" "$(call Line,$(WIDTH),=)" "$(NO_COLOR)"
	printf "%b\n" "$(WHITE)Compleated Compiling $(NAME)$(NO_COLOR)"

.PHONY : clean
clean: start-clean source-clean test-clean
	#if [[ -e compile_commands.json ]]; then rm compile_commands.json; fi
	#if [[ -e $(BUILD_DIR)/lib$(NAME).a ]]; then rm $(BUILD_DIR)/lib$(NAME).a; fi
	printf "%b%s%b\n" "$(CLEAN_COLOR)" "$(call Line,$(WIDTH),=)" "$(NO_COLOR)"
	printf "%b\n" "$(CLEAN_COLOR)Compleated Cleaning$(NO_COLOR)"

.PHONY : purge
purge: uninstall clean

.PHONY : new
new: clean all

.PHONY : docs
docs: docs-html docs-latex

.PHONY : docs-html
docs-html:
	cd docs && $(MAKE) html

.PHONY : docs-latex
docs-latex:
	cd docs && $(MAKE) latexpdf

.PHONY : install
ifeq ($(TYPE),lib)
install: all
	$(eval SOURCE_HEADERS = $(shell cd $(SOURCE_DIR) && find . -name '*.hpp' -or -name '*.h'))
	$(eval LIB_OBJ = $(filter-out $(BASE_PATH)/$(BUILD_DIR)/$(SOURCE_DIR)/main.o, $(shell find $(BASE_PATH)/$(BUILD_DIR)/$(SOURCE_DIR)/*.o)))
	@if [[ $$UID != 0 ]]; then \
	  printf "%b\n" "$(ERR_COLOR)Must run with root permissions$(NO_COLOR)"; \
	else \
	  printf "%b\n" "$(INSTALL_COLOR)Installing $(NAME) lib$(NO_COLOR)"; \
	  printf "%b%s%b\n" "$(INSTALL_COLOR)" "$(call Line,$(WIDTH),=)" "$(NO_COLOR)"; \
	  $(call Print,Compiling library,$(WIDTH)); \
	  sudo ar rcs $(BUILD_DIR)/lib$(NAME).a $(LIB_OBJ); \
	  if [[ -e $(BUILD_DIR)/lib$(NAME).a ]]; then \
	    $(call check); \
	    $(call Print,Copying library,$(WIDTH)); \
	    sudo cp $(BUILD_DIR)/lib$(NAME).a $(LIB_PATH)/lib/ -u; \
	    $(call check); \
	    $(call Print,Copying headers,$(WIDTH)); \
	    if [[ ! -d $(LIB_PATH)/include/$(NAME) ]]; then sudo mkdir $(LIB_PATH)/include/$(NAME); fi;\
	    cd $(SOURCE_DIR) && sudo cp $(SOURCE_HEADERS) $(LIB_PATH)/include/$(NAME)/ -r -u ; \
	    $(call check); \
	  else \
	    $(call cross); \
	  fi;\
	  printf "%b%s%b\n" "$(INSTALL_COLOR)" "$(call Line,$(WIDTH),=)" "$(NO_COLOR)"; \
	  printf "%b\n" "$(INSTALL_COLOR)Installed $(NAME) lib$(NO_COLOR)"; \
	fi 

else
install:all
	printf "%b\n" "$(INSTALL_COLOR)Installing $(NAME)$(NO_COLOR)"
	printf "%b%s%b\n" "$(INSTALL_COLOR)" "$(call Line,$(WIDTH),=)" "$(NO_COLOR)"
	$(call Print,Copying $(NAME),$(WIDTH))
	cp $(NAME) $(EXE_PATH) -u
	$(call check)
	printf "%b%s%b\n" "$(INSTALL_COLOR)" "$(call Line,$(WIDTH),=)" "$(NO_COLOR)"; \
	printf "%b\n" "$(INSTALL_COLOR)Installed $(NAME)$$(NO_COLOR)"; \

endif

.PHONY : uninstall
ifeq ($(TYPE),lib)
uninstall:
	@if [[ $$UID != 0 ]]; then \
	  printf "%b\n" "$(ERR_COLOR)Must run with root permissions$(NO_COLOR)"; \
	else \
	  printf "%b\n" "$(INSTALL_COLOR)Uninstalling $(NAME) lib$(NO_COLOR)"; \
	  printf "%b%s%b\n" "$(INSTALL_COLOR)" "$(call Line,$(WIDTH),=)" "$(NO_COLOR)"; \
	  if [[ -e $(LIB_PATH)/lib/lib$(NAME).a ]]; then \
	    $(call Print,Deleting library,$(WIDTH)); \
	    sudo rm $(LIB_PATH)/lib/lib$(NAME).a; \
	    $(call check); \
	  fi; \
	  if [[ -d $(LIB_PATH)/include/$(NAME) ]]; then \
	    $(call Print,Deleting header files,$(WIDTH)); \
	    sudo rm $(LIB_PATH)/include/$(NAME)/ -r; \
	    $(call check); \
	  fi; \
	  printf "%b%s%b\n" "$(INSTALL_COLOR)" "$(call Line,$(WIDTH),=)" "$(NO_COLOR)"; \
	  printf "%b\n" "$(INSTALL_COLOR)Uninstalled $(NAME) lib$(NO_COLOR)"; \
	fi 


else
uninstall:
	printf "%b\n" "$(INSTALL_COLOR)Uninstalling $(NAME)$(NO_COLOR)"
	printf "%b%s%b\n" "$(INSTALL_COLOR)" "$(call Line,$(WIDTH),=)" "$(NO_COLOR)"
	$(call Print,Deleting ~/bin/$(NAME),$(WIDTH))
	rm $(NAME) $(EXE_PATH) -u
	$(call check)
	printf "%b%s%b\n" "$(INSTALL_COLOR)" "$(call Line,$(WIDTH),=)" "$(NO_COLOR)"; \
	printf "%b\n" "$(INSTALL_COLOR)Uninstalled $(NAME)$$(NO_COLOR)"; \

endif

.PHONY : start
start:
	printf "%b\n" "$(WHITE)Compiling $(NAME)$(NO_COLOR)"
	printf "%b%s%b\n" "$(WHITE)" "$(call Line,$(WIDTH),=)" "$(NO_COLOR)"

.PHONY : start-clean
start-clean:
	printf "%b\n" "$(CLEAN_COLOR)Cleaning $(NAME)$(NO_COLOR)"
	printf "%b%s%b\n" "$(CLEAN_COLOR)" "$(call Line,$(WIDTH),=)" "$(NO_COLOR)"

.PHONY : source-make
source-make:
	printf "%b\n" "$(BUILD_COLOR)SOURCE$(NO_COLOR)"
	cd $(SOURCE_DIR) && $(MAKE)

.PHONY : source-clean
source-clean:
	printf "%b\n" "$(CLEAN_COLOR)SOURCE$(NO_COLOR)"
	cd $(SOURCE_DIR) && $(MAKE) clean

.PHONY : test-make
test-make:
	if [[ -z "$(TEST_DIR)" ]] && [[ -d "$(TEST_DIR)" ]]; then \
	  printf "%b\n" "$(BUILD_COLOR)TEST$(NO_COLOR)"; \
	  cd $(TEST_DIR) && $(MAKE); \
	fi

.PHONY : test-clean
test-clean:
	if [[ -z "$(TEST_DIR)" ]] && [[ -d "$(TEST_DIR)" ]]; then \
	  printf "%b\n" "$(CLEAN_COLOR)TEST$(NO_COLOR)"; \
	  cd $(TEST_DIR) && $(MAKE) clean; \
	fi

