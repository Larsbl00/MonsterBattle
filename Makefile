#File info
VERSION=0.2
NAME=MonsterBattle
DEBUG_NAME=$(NAME)-debug
RELEASE_NAME=$(NAME)-release

#Compiler and flags
CXX=g++
CXX_FLAGS=-Wall -Wextra -Werror -std=c++1z -DVERSION=$(VERSION)

DEBUG_FLAGS=-O0 -g -DBUILD_TYPE=DEBUG
RELEASE_FLAGS=-O3 -DBUILD_TYPE=RELEASE

#Setup platform specific variables 
ifeq ($(OS),Windows_NT)
    LIB_EXT:=.dll
	EXTENSION=.exe
else
    LIB_EXT:=.so
	EXTENSION=.out
endif


####################################
# Add additional linking flags
####################################
LD_FLAGS=\
	-lpthread

####################################
# Add inclusion directories
####################################
INC_FLAGS=\
	-I$(INC_DIR) \
	-I$(INC_DIR)/Interfaces


#Directories
LIB_DIR=./lib
SRC_DIR=./src
INC_DIR=./include
BLD_DIR=./build
OBJ_DIR=$(BLD_DIR)/obj
DEBUG_OBJ_DIR=$(OBJ_DIR)/$(DEBUG_NAME)
RELEASE_OBJ_DIR=$(OBJ_DIR)/$(RELEASE_NAME)

########################################
#
#              Files
#
########################################

# You only need to change these files for the Libs, sources and headers respectively
# Each lib placed here should be a directory containing the cpp and h file of the lib
#
#	lib
#	|- Foo
#	  |- Foo.cpp
#	  |- Foo.h
#
LIBS=\

#########################################
# Add your source files and headers here
#########################################
SRC=\
	main.cpp \
	InputReader.cpp\
	TerminalInputReader.cpp \
	Game.cpp \
	TerminalDisplay.cpp \
	DisplayManager.cpp \
	TypeWeaknessManager.cpp \
	Monster.cpp \
	Sprite.cpp \
	Model.cpp \
	RaiiFileHandle.cpp \
	Color.cpp \
	AnsiEffects.cpp \
	Move.cpp \
	Stats.cpp \
	MoveManager.cpp \
	Type.cpp \
	TypeColorManager.cpp \
	MonsterManager.cpp \
	Trainer.cpp \
	MonsterBattle.cpp \
	DisplayableText.cpp \
	DisplayableTextManager.cpp \

HEADERS=\
	$(INC_DIR)/$(wildcard *.h)


# Clean up and sort entered details
SRC:=$(sort $(SRC))
HEADERS:=$(sort $(HEADERS))

# Objects
OBJECTS=$(addprefix $(OBJ_DIR)/, $(SRC:.cpp=.o))
DEBUG_OBJECTS=$(addprefix $(DEBUG_OBJ_DIR)/, $(notdir $(OBJECTS)))
RELEASE_OBJECTS=$(addprefix $(RELEASE_OBJ_DIR)/, $(notdir $(OBJECTS)))
ifneq ($(LIBS), ) #If there are no libs, skip this
	LIBS:=$(addprefix $(LIB_DIR)/, $(LIBS)/$(LIBS)$(LIB_EXT))
endif

#generate linking flags
LD_FLAGS:=$(LD_FLAGS) $(addprefix -L, $(dir $(LIBS))) $(addprefix -l, $(basename $(notdir $(LIBS))))
INC_FLAGS:=$(INC_FLAGS) $(addprefix -I, $(dir $(LIBS)))

#Vpaths
vpath %.h $(INC_DIR) $(sort $(dir $(HEADERS)))
vpath %.cpp  $(SRC_DIR) $(sort $(dir $(SRC)))
vpath $(LIB_EXT) $(LIB_DIR)

#######################################
#
#                Targets
#
#######################################
.PHONY: all dirs clean lib

all: dirs $(NAME) $(DEBUG_NAME) $(RELEASE_NAME)

$(NAME): $(DEBUG_NAME) $(RELEASE_NAME)

$(DEBUG_NAME): dirs $(DEBUG_OBJECTS)
	$(CXX) $(CXX_FLAGS) $(DEBUG_FLAGS) $(INC_FLAGS) $(DEBUG_OBJECTS) -o $(BLD_DIR)/$@$(EXTENSION) $(LD_FLAGS) 

$(RELEASE_NAME): dirs $(RELEASE_OBJECTS)
	$(CXX) $(CXX_FLAGS) $(RELEASE_FLAGS) $(INC_FLAGS) $(RELEASE_OBJECTS) -o $(BLD_DIR)/$@-$(subst .,-,$(VERSION))$(EXTENSION) $(LD_FLAGS) 

debug: $(DEBUG_NAME)

release: $(RELEASE_NAME)

lib: $(LIBS)

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
	$(CXX) $(CXX_FLAGS) $(INC_FLAGS) -c $< -o $@ 

$(DEBUG_OBJ_DIR)/%.o: %.cpp Makefile
	$(CXX) $(CXX_FLAGS) $(DEBUG_FLAGS) $(INC_FLAGS) -c $< -o $@ 

$(RELEASE_OBJ_DIR)/%.o: %.cpp Makefile
	$(CXX) $(CXX_FLAGS) $(RELEASE_FLAGS) $(INC_FLAGS) -c $< -o $@ 

%$(LIB_EXT): %.cpp | %.h
	$(CXX) $(CXX_FLAGS) -fPIC -shared -c $^ -o $(addprefix $(dir $@)lib, $(notdir $@))
