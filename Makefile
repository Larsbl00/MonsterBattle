#File info
VERSION=0.1
NAME=MonsterBattle
DEBUG_NAME=$(NAME)-debug
RELEASE_NAME=$(NAME)-release

#Compiler and flags
CXX=g++
CXX_FLAGS=-Wall -Wextra -Werror

DEBUG_FLAGS=-O0 -g
RELEASE_FLAGS=-O3

#Setup platform specific variables 
ifeq ($(OS),Windows_NT)
    LIB_EXT:=.dll
	EXTENSION=.exe
else
    LIB_EXT:=.so
	EXTENSION=.out
endif


# You need to add all inclusions and libs in here
LD_FLAGS=\
	-LTestClass

INC_FLAGS=\
	-I$(INC_DIR)


#Directories
LIB_DIR=./lib
SRC_DIR=./src
INC_DIR=./include
BLD_DIR=./build
OBJ_DIR=./obj
DEBUG_OBJ_DIR=$(OBJ_DIR)/$(DEBUG_NAME)
RELEASE_OBJ_DIR=$(OBJ_DIR)/$(RELEASE_NAME)

########################################
#
#              Files
#
########################################

# You only need to change these files for the Libs, sources and headers respectively
SRC=\
	main.cpp

HEADERS=\
	$(INC_DIR)/$(wildcard *.h)

# Objects
OBJECTS=$(addprefix $(OBJ_DIR)/, $(SRC:.cpp=.o))
DEBUG_OBJECTS=$(addprefix $(DEBUG_OBJ_DIR)/, $(notdir $(OBJECTS)))
RELEASE_OBJECTS=$(addprefix $(RELEASE_OBJ_DIR)/, $(notdir $(OBJECTS)))
LD_FLAGS:=$(addprefix -L, $(LIBS))
LIBS:=$(addprefix $(LIB_DIR)/, $(LIBS))

#Vpaths
vpath %.h $(INC_DIR)
vpath %.cpp $(SRC_DIR)

#######################################
#
#                Targets
#
#######################################
.PHONY: all dirs clean

all: dirs $(NAME) $(DEBUG_NAME) $(RELEASE_NAME)

$(NAME): dirs $(OBJECTS)
	$(CXX) $(CXX_FLAGS) $(INC_FLAGS) $(LD_FLAGS) $(OBJECTS) -o $(BLD_DIR)/$@$(EXTENSION)

$(DEBUG_NAME): dirs $(DEBUG_OBJECTS)
	$(CXX) $(CXX_FLAGS) $(DEBUG_FLAGS) $(INC_FLAGS) $(LD_FLAGS) $(DEBUG_OBJECTS) -o $(BLD_DIR)/$@$(EXTENSION)

$(RELEASE_NAME): dirs $(RELEASE_OBJECTS)
	$(CXX) $(CXX_FLAGS) $(RELEASE_FLAGS) $(INC_FLAGS) $(LD_FLAGS) $(RELEASE_OBJECTS) -o $(BLD_DIR)/$@-$(subst .,-,$(VERSION))$(EXTENSION)

dirs:
	@mkdir -p $(LIB_DIR)
	@mkdir -p $(SRC_DIR)
	@mkdir -p $(INC_DIR)
	@mkdir -p $(BLD_DIR)
	@mkdir -p $(OBJ_DIR)
	@mkdir -p $(DEBUG_OBJ_DIR)
	@mkdir -p $(RELEASE_OBJ_DIR)

clean:
	@rm -rf $(DEBUG_OBJ_DIR)
	@rm -rf $(RELEASE_OBJ_DIR)
	@rm -rf $(OBJ_DIR)
	@rm -rf $(BLD_DIR)

#Compilers
#Makefile is used for the header dependency
$(OBJ_DIR)/%.o: %.cpp Makefile
	$(CXX) $(CXX_FLAGS) $(LD_FLAGS) $(INC_FLAGS) -c $< -o $@

$(DEBUG_OBJ_DIR)/%.o: %.cpp Makefile
	$(CXX) $(CXX_FLAGS) $(DEBUG_FLAGS) $(LD_FLAGS) $(INC_FLAGS) -c $< -o $@

$(RELEASE_OBJ_DIR)/%.o: %.cpp Makefile
	$(CXX) $(CXX_FLAGS) $(RELEASE_FLAGS) $(LD_FLAGS) $(INC_FLAGS) -c $< -o $@