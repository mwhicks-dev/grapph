CCC = g++
CFLAGS = -Wall -g -fPIC -I./include
CCFLAGS = -shared
DFLAGS =

LIB_NAME = libgrapph
LIB_VERSION = 0.1.0

SRC_FOLDER = src
OBJ_FOLDER = obj
BIN_FOLDER = bin

ALL_NAMES = Graph.o
ALL_OBJS = $(foreach obj, $(ALL_NAMES), $(OBJ_FOLDER)/$(obj))

libgrapph: setup $(ALL_OBJS)
	$(info -> compiling library)
	$(CCC) $(CFLAGS) $(CCFLAGS) -o $(BIN_FOLDER)/$(LIB_NAME)_$(LIB_VERSION).a $(ALL_OBJS)

setup:
	mkdir -p $(BIN_FOLDER) $(OBJ_FOLDER)

clean:
	rm -f $(OBJ_FOLDER)/* $(BIN_FOLDER)/*

$(ALL_OBJS) : $(OBJ_FOLDER)/%.o : $(SRC_FOLDER)/%.cpp
	$(info -> $@: compiling object)
	$(CCC) $(CFLAGS) -c $< -o $@