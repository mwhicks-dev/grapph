CCC = g++ -std=c++17
CFLAGS = -Wall -g -I./include
CCFLAGS = -static
DFLAGS =

LIB_NAME = libgrapph
LIB_VERSION = 2.0.2

SRC_FOLDER = src
OBJ_FOLDER = obj
BIN_FOLDER = bin

ALL_NAMES = Graph.o Homomorphism.o
ALL_OBJS = $(foreach obj, $(ALL_NAMES), $(OBJ_FOLDER)/$(obj))

lib: setup $(ALL_OBJS)
	$(info -> compiling libgrapph)
	ar rcs $(BIN_FOLDER)/$(LIB_NAME)_$(LIB_VERSION).a $(ALL_OBJS)

setup:
	mkdir -p $(BIN_FOLDER) $(OBJ_FOLDER)

clean:
	rm -f $(OBJ_FOLDER)/* $(BIN_FOLDER)/*

$(ALL_OBJS) : $(OBJ_FOLDER)/%.o : $(SRC_FOLDER)/%.cpp
	$(info -> $@: compiling object)
	$(CCC) $(CFLAGS) -c $< -o $@