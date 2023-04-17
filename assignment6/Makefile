DIR_SRC = src
DIR_BIN = bin
DIR_TEMP = temp
DIR_OBJ = obj

SRC = $(wildcard $(DIR_TEMP)/*.cpp)
OBJ = $(patsubst $(DIR_TEMP)/%.cpp, $(DIR_OBJ)/%.o, $(SRC))

TARGET = main
BIN_TARGET = $(DIR_BIN)/$(TARGET)

CC = g++
CFLAGS = -std=c++11 -O3 -lstdc++

$(BIN_TARGET): $(OBJ)
	$(CC) $(CFLAGS) $^ -o $@

$(DIR_OBJ)/%.o: $(DIR_TEMP)/%.cpp
	$(CC) $(CFLAGS) -c $^ -o $@

.PHONY: clean
clean:
	rm -f $(DIR_OBJ)/*.o $(BIN_TARGET)
	rm -f $(DIR_TEMP)/*.cpp
	rm -f $(DIR_TEMP)/*.hpp