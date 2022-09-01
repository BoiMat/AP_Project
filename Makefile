CC = g++
VERSION = c++17

SRC_PATH = src
OBJ_PATH = obj
BIN_PATH = bin

$(OBJ_PATH)/main.o: $(SRC_PATH)/main.cpp
	$(CC) -o $(OBJ_PATH)/main.x $(SRC_PATH)/main.cpp

clean:
	$(RM) $(OBJ_PATH)/main.x
