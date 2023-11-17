CC = g++
CFLAGS = -Wall -Wextra -std=c++17 -lstdc++fs
SRC_DIR = src
OBJ_DIR = obj

SRC = $(wildcard $(SRC_DIR)/*.cpp)

OBJ = $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SRC))

EXEC = bomberStudent

all : $(EXEC)

bomberStudent : $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^ -lstdc++fs

$(OBJ_DIR)/main.o : $(SRC_DIR)/main.cpp
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.cpp $(SRC_DIR)/%.h
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

clean :
	rm -f  $(OBJ) $(EXEC)

.PHONY: clean all
