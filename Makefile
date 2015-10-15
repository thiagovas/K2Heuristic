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

k2: database
	$(CC) -c $(SRC_DIR)/k2.cc -o $(OBJ_DIR)/k2.o

database: document
	$(CC) -c $(SRC_DIR)/database.cc -o $(OBJ_DIR)/database.o

document:
	$(CC) -c $(SRC_DIR)/document.cc -o $(OBJ_DIR)/document.o

clean:
	rm -rf ./obj/*.o
	rm -rf *~
	rm -f main
