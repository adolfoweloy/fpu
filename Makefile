OUTPUT=main
CC=gcc
BIN_DIR=bin

run: all
	time ./$(BIN_DIR)/$(OUTPUT)

all: prepare $(OUTPUT).o
	$(CC) $(OUTPUT).o -o $(BIN_DIR)/$(OUTPUT) -lpthread -lm

$(OUTPUT).o: $(OUTPUT).c
	$(CC) -c $(OUTPUT).c

prepare: clean
	mkdir $(BIN_DIR)

clean:
	rm -f *.o
	rm -Rf $(BIN_DIR)

