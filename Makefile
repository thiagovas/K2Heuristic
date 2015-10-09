CC=g++
SRC_DIR=./src
OBJ_DIR=./obj

build: prep main
	$(CC) $(OBJ_DIR)/* -o main

prep:
	mkdir -p $(OBJ_DIR)

run:
	./main

main: k2
	$(CC) -c $(SRC_DIR)/main.cc -o $(OBJ_DIR)/main.o

k2:
	$(CC) -c $(SRC_DIR)/k2.cc -o $(OBJ_DIR)/k2.o

clean:
	rm -rf ./obj/*.o
	rm -rf *~
	rm -f main
