CC = g++
VERSION = c++17

SRC_PATH = src
OBJ_PATH = obj

$(OBJ_PATH)/main.x: $(SRC_PATH)/main.cpp
	$(CC) -o $(OBJ_PATH)/main.x $(SRC_PATH)/main.cpp

$(OBJ_PATH)/test.x: $(SRC_PATH)/test.cpp
	$(CC) -o $(OBJ_PATH)/test.x $(SRC_PATH)/test.cpp

clean:
	$(RM) $(OBJ_PATH)/*