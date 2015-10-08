CC=g++
SRC_DIR=./src
OBJ_DIR=./obj

build: prep main
	$(CC) $(OBJ_DIR)/* -o main

prep:
	mkdir -p $(OBJ_DIR)

run:
	./main

main: graph
	$(CC) -c $(SRC_DIR)/main.cc -o $(OBJ_DIR)/main.o

graph:
	$(CC) -c $(SRC_DIR)/graph.cc -o $(OBJ_DIR)/graph.o

clean:
	rm -rf ./obj/*.o
	rm -rf *~
	rm -f main
