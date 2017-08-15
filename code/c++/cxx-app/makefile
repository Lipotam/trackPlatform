#Make file to compile source code for track platform cxx api library

#Project Name
PROJECT_NAME            		= track-platform_cxx-app
#Build option
BUILD							?= BUILD_STATIC
#ANSI Colos
ANSI_COLOR_RED                  = \e[31m
ANSI_COLOR_GREEN                = \e[32m
ANSI_COLOR_YELLOW               = \e[33m
ANSI_COLOR_BLUE                 = \e[34m
ANSI_COLOR_MAGENTA              = \e[35m
ANSI_COLOR_CYAN                 = \e[36m
ANSI_COLOR_RESET                = \e[37m
################################Compiller flags###############################################################
#Opitmization Level
OPT_LEVEL						= -O0
#Warning options
WARNINGS 						= -Wall -Wpedantic #-Werror
# WARNINGS 						+= -fsyntax-only	# for syntax checking only, without comlipation
WARNINGS_WITHOUT				=
#User Compiller flags
USER_FLAGS						?=
##############################################################################################################
# OS redefinition
OS 								= $(shell uname -s)

#Build patch
BUILD_PATH              		= Output/$(OS)
OBJ_PATH	              		= $(BUILD_PATH)/obj

#Compiller flags
CFLAGS                  		= $(OPT_LEVEL)
CFLAGS							+= -g0
CFLAGS							+= $(WARNINGS)
CFLAGS							+= -I.
CFLAGS							+= $(USER_FLAGS)
CFLAGS                  		+= -std=c++11
CFLAGS							+= -D$(BUILD)
# ifeq ($(BUILD), BUILD_STATIC)
# CFLAGS							+= -D$(BUILD_STATIC)
# endif

CFLAGS                  		+= $(INCLUDES)
##############################################################################################################
#Code file path
OTHER_PATH						= .
OTHER_SOURCE_PATH				= $(OTHER_PATH)
OTHER_INCLUDE_PATH				= $(OTHER_PATH)

#library path
API_PATH						= ../cxx-api
API_INCLUDE_PATH				= $(API_PATH)
API_BUILD_PATH					= $(API_PATH)/$(BUILD_PATH)

ifeq ($(BUILD), BUILD_STATIC)
API_NAME						= track-platform_cxx-api.a
else
ifeq ($(BUILD), BUILD_DYNAMIC)
API_NAME						= track-platform_cxx-api.so
endif
endif

API_FULL_PATH					= $(API_BUILD_PATH)/$(API_NAME)

#Linker scrpit file
ARFLAGS							=

#Source file path

SOURCES							=
# Other code (non grouped)
SOURCES							+= $(OTHER_SOURCE_PATH)/main.cpp

#Include file path
INCLUDES                		=
INCLUDES                		+= -I$(API_INCLUDE_PATH)
# INCLUDES                		+= -I$(OTHER_INCLUDE_PATH)

##############################################################################################################
BUILD_PRINT						= $(ANSI_COLOR_GREEN) Building:$(ANSI_COLOR_RESET) $@
##############################################################################################################
#Output files
BIN								= $(BUILD_PATH)/$(PROJECT_NAME)

OBJECTS                 		= $(addprefix $(OBJ_PATH)/, $(addsuffix .o, $(basename $(SOURCES))))

STATIC_LIB: $(OBJECTS) api
	@$(CXX) -o $(BIN) $(OBJECTS) $(API_FULL_PATH)
	@echo -e "$(BUILD_PRINT)"

DYNAMIC_LIB: $(OBJECTS) api
	$(error Dynamic library is not supported yet)
	# @$(CXX) -shared -o $(BIN) $(OBJECTS)
	@echo -e "$(BUILD_PRINT)"

$(OBJ_PATH)/%.o: %.cc
	@mkdir -p $(dir $@)
	@$(CXX) -c $(CFLAGS) $< -o $@
	@echo -e "$(BUILD_PRINT)"

$(OBJ_PATH)/%.o: %.cpp
	@mkdir -p $(dir $@)
	@$(CXX) -c $(CFLAGS) $< -o $@
	@echo -e "$(BUILD_PRINT)"

#Makefile parameters
.DEFAULT_GOAL := all

all: build

ifeq ($(BUILD), BUILD_STATIC)
build: STATIC_LIB

else
ifeq ($(BUILD), BUILD_DYNAMIC)
build: DYNAMIC_LIB

else
build:
	@echo "That BUILD variable is not supported. Use `make help` to see supported variants of build variable"
endif
endif

dynamic:
	$(MAKE) BUILD=BUILD_DYNAMIC

static:
	$(MAKE) BUILD=BUILD_STATIC

api:
	$(MAKE) -C $(API_PATH) BUILD=$(BUILD)

clean:
	@rm -rf $(BUILD_PATH)
	$(MAKE) -C $(API_PATH) $@

run:
	@$(BIN)

set_def_color:
	@echo -e "$(ANSI_COLOR_RESET)"

help:
	@echo "$(NEW_LINE)"
	@echo "\tall : Builds static or dynamic library (static by default)"
	@echo "\t\tIf you want to build static library(.a file), write `make` or `make static` or `make BUILD=BUILD_DYNAMIC`"
	@echo "\t\tIf you want to build dynamic library(.so file), write `make dynamic` or `make BUILD=BUILD_DYNAMIC`"
	@echo "$(NEW_LINE)"
