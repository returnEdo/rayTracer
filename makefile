CC := g++
SRC_FILES := $(wildcard *.cpp)
OBJ_FILES := $(patsubst %.cpp,%.o,$(SRC_FILES))
#LIST := $(addprefix $(BIN_DIR)/,$(OBJ_FILES))

main: $(OBJ_FILES)
	$(CC) $^ -o $@

$%.o: %.cpp
	$(CC) $< -c $@ 

clean:
	rm *.o
