SRC = src
INC = include
OBJ = obj
BIN = bin
CPPFLAGS = -Wall -O2 -g -c -std=c++17 -I$(INC) 

all: $(BIN)/main 

$(BIN)/main: $(OBJ)/main.o $(OBJ)/utilities.o $(OBJ)/Context.o  $(OBJ)/BatchAlgorithms.o $(OBJ)/IncrementalAlgorithms.o
	$(CXX) $^ -o $@

$(OBJ)/%.o: $(SRC)/%.cpp
	$(CXX) $(CPPFLAGS) $^ -o $@

clean:
	-rm obj/* bin/*
