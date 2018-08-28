TARGET = wofsim 
SRC_DIR = src
INC_DIR = include
OBJ_DIR = obj

SRC = $(wildcard $(SRC_DIR)/*.cpp)
OBJS = $(SRC:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)

CC = g++
CPPFLAGS = -std=c++11 -I$(INC_DIR)
CFLAGS = -Wall

.PHONY: clean show

$(TARGET): $(OBJS)
	$(CC) $^ -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@test -d obj || mkdir -p obj
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ_DIR)/*.o *~ core $(TARGET)

show:
	@echo $(OBJS)
	@echo $(SRC)
