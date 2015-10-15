CC=g++
SRC_DIR=./src
OBJ_DIR=./obj
STD=c++11
OPTM=O2

build: prep main
	$(CC) $(OBJ_DIR)/* -o main

prep:
	mkdir -p $(OBJ_DIR)

run:
	./main

main: k2
	$(CC) -c $(SRC_DIR)/main.cc -o $(OBJ_DIR)/main.o -std=$(STD) -$(OPTM)

k2: database
	$(CC) -c $(SRC_DIR)/k2.cc -o $(OBJ_DIR)/k2.o -std=$(STD) -$(OPTM)

database: document
	$(CC) -c $(SRC_DIR)/database.cc -o $(OBJ_DIR)/database.o -std=$(STD) -$(OPTM)

document:
	$(CC) -c $(SRC_DIR)/document.cc -o $(OBJ_DIR)/document.o -std=$(STD) -$(OPTM)

indextree:
	$(CC) -c $(SRC_DIR)/indextree.cc -o $(OBJ_DIR)/indextree.o -std=$(STD) -$(OPTM)

clean:
	rm -rf ./obj/*.o
	rm -rf *~
	rm -f main
