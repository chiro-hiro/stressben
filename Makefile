CC=g++
TARGET=stressben
LIBS=-lpthread
FLAGS=-std=c++11
BIN_DIR=/usr/bin/

CUR_DIR=$(shell dirname $(realpath $(lastword $(MAKEFILE_LIST))))
BLD_DIR=$(CUR_DIR)/build/
SRC_DIR=$(CUR_DIR)/src/
INC_DIR=-I$(SRC_DIR)

SOURCE_FILES=threadPool randomize tcpClient utilities main
OBJECT_FILES= $(foreach filename,$(SOURCE_FILES),$(BLD_DIR)$(filename).o)

default:
	mkdir -p $(BLD_DIR)
	for filename in $(SOURCE_FILES) ; do \
		$(CC) $(FLAGS) $(CFLAGS) -c $(SRC_DIR)$$filename.cpp -o $(BLD_DIR)$$filename.o $(INC_DIR); \
	done
	$(CC) $(OBJECT_FILES) -o $(BLD_DIR)$(TARGET) $(LIBS)
	
install:
	rm -rf $(BIN_DIR)$(TARGET)
	cp $(BLD_DIR)$(TARGET) $(BIN_DIR)$(TARGET)

uninstall:
	rm -rf $(BIN_DIR)$(TARGET)

clean:
	rm -rf $(BLD_DIR)*
