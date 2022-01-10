#Used compiler
CC = g++

# APP name
APP_NAME = Boids
APP_FNAME = /$(APP_NAME).cpp

# Directories
SRC_DIR := ./src
APP_DIR := ./App
APP_SRC_DIR := ./App/classes
ENGINE_SRCS_DIR := $(SRC_DIR)/jellyfish
#GAME_SRCS_DIR := /
GLAD_SRCS_DIR := $(SRC_DIR)/glad
#GLM_SRCS_DIR := $(SRC_DIR)/glm
STBI_SRCS_DIR := $(SRC_DIR)/stbi

# Source files
ENGINE_SRCS = $(wildcard $(ENGINE_SRCS_DIR)/*.cpp)
#GAME_SRCS = $(wildcard $(GAME_SRCS_DIR)/*.cpp)
GLAD_SRCS = $(wildcard $(GLAD_SRCS_DIR)/*.c)
#GLM_SRCS = $(wildcard $(GLM_SRCS_DIR)/*.c)
STBI_SRCS = $(wildcard $(STBI_SRCS_DIR)/*.cpp)

# App
APP_SRCS = $(wildcard $(APP_SRC_DIR)/*.cpp)

# Object files
ENGINE_OBJS = $(ENGINE_SRCS:.cpp=.o)
#GAME_OBJS = $(GAME_SRCS:.cpp=.o)
GLAD_OBJS = $(GLAD_SRCS:.c=.o)
#GLM_OBJS = $(GLM_SRCS:.c=.o)
STBI_OBJS = $(STBI_SRCS:.cpp=.o)
APP_OBJS = $(APP_SRCS:.cpp=.o)

#Path to aditional files needed to compile
INCLUDE_PATHS = -Iinclude

#Path to libraries needed to compile
LIBRARY_PATHS = -Llibs

#Aditional compile options
COMPILER_FLAGS = -g

#Specifies which libraries we're linking
LINKER_FLAGS = -lglfw3 -lOpenGL32

#Executable name
EXE_NAME = App/$(APP_NAME).exe

all : main 

main:  $(GLAD_OBJS) $(STBI_OBJS) $(APP_OBJS) $(ENGINE_OBJS)
	$(CC) $(STBI_OBJS) $(GLM_OBJS) $(GLAD_OBJS) $(APP_OBJS) $(ENGINE_OBJS) $(APP_DIR)$(APP_FNAME) $(INCLUDE_PATHS) $(LIBRARY_PATHS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(EXE_NAME)

%.o: %.cpp
	$(CC) -c $(INCLUDE_PATHS) $(LIBRARY_PATHS) $< -o $@

%.o: %.c
	$(CC) -c $(INCLUDE_PATHS) $(LIBRARY_PATHS) $< -o $@

clean:
	del $(subst /,\\,$(ENGINE_SRCS_DIR))\*.o & del $(subst /,\\,$(GAME_SRCS_DIR))\*.o & del $(subst /,\\,$(GLAD_SRCS_DIR))\*.o & del $(subst /,\\,$(STBI_SRCS_DIR))\*.o