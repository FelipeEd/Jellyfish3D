#Used compiler
CC = g++

# APP name
NAME := Boids
APP_NAME := $(NAME)App
APP_FNAME := /$(APP_NAME).cpp

# Directories
SRC_DIR := ./src
INCLUDE_DIR := ./include
APP_DIR := $(APP_NAME)
APP_SRC_DIR := $(APP_DIR)/classes

GLAD_SRCS_DIR := $(INCLUDE_DIR)/glad
STBI_SRCS_DIR := $(INCLUDE_DIR)/stbi
IMGUI_SRCS_DIR := $(INCLUDE_DIR)/imgui

ENGINE_SRCS_DIR := $(SRC_DIR)/jellyfish

# Source files
GLAD_SRCS = $(wildcard $(GLAD_SRCS_DIR)/*.c)
STBI_SRCS = $(wildcard $(STBI_SRCS_DIR)/*.cpp)
IMGUI_SRCS = $(wildcard $(IMGUI_SRCS_DIR)/*.cpp)

ENGINE_SRCS = $(wildcard $(ENGINE_SRCS_DIR)/*.cpp)

# App
APP_SRCS = $(wildcard $(APP_SRC_DIR)/*.cpp)

# Object files
GLAD_OBJS = $(GLAD_SRCS:.c=.o)
STBI_OBJS = $(STBI_SRCS:.cpp=.o)
IMGUI_OBJS = $(IMGUI_SRCS:.cpp=.o)

ENGINE_OBJS = $(ENGINE_SRCS:.cpp=.o)

APP_OBJS = $(APP_SRCS:.cpp=.o)

#Path to aditional files needed to compile
INCLUDE_PATHS = -Iinclude -I$(SRC_DIR)

#Path to libraries needed to compile
LIBRARY_PATHS = -Llibs

#Aditional compile options
COMPILER_FLAGS = -O2 

#Specifies which libraries we're linking
LINKER_FLAGS = -lglfw3 -lOpenGL32 

#Executable name
EXE_NAME = bin/$(APP_NAME).exe

all : main 

main: $(IMGUI_OBJS) $(GLAD_OBJS) $(STBI_OBJS) $(APP_OBJS) $(ENGINE_OBJS)
	$(CC) $(IMGUI_OBJS) $(STBI_OBJS) $(GLM_OBJS) $(GLAD_OBJS) $(APP_OBJS) $(ENGINE_OBJS) $(APP_DIR)$(APP_FNAME) $(INCLUDE_PATHS) $(LIBRARY_PATHS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(EXE_NAME)

%.o: %.cpp
	$(CC) -c $(INCLUDE_PATHS) $(LIBRARY_PATHS) $< -o $@

%.o: %.c
	$(CC) -c $(INCLUDE_PATHS) $(LIBRARY_PATHS) $< -o $@

clean:
	del $(subst /,\\,$(ENGINE_SRCS_DIR))\*.o
cleanDeep:
	del $(subst /,\\,$(ENGINE_SRCS_DIR))\*.o & del $(subst /,\\,$(IMGUI_SRCS_DIR))\*.o & del $(subst /,\\,$(GLAD_SRCS_DIR))\*.o & del $(subst /,\\,$(STBI_SRCS_DIR))\*.o