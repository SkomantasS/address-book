BIN := address_book_program
CFLAGS := -Wall -Wextra -std=c99 -g

BIN_DIR := ./bin
BLD_DIR := ./build
INC_DIR := ./inc
LIB_DIR := ./lib
PWD := $(shell pwd)
SRC_DIR := ./src

lib_names := address_book

.PHONY: all
all:$(BIN_DIR)/$(BIN)

$(BIN_DIR)/$(BIN):builddeps
	mkdir -p $(BIN_DIR)
	$(CC)  $(CFLAGS) -I$(INC_DIR) -o $@ $(BLD_DIR)/*.o -L$(LIB_DIR) -l$(lib_names)

.PHONY: builddeps
builddeps:
	cd $(SRC_DIR) && $(MAKE)
	cd $(LIB_DIR) && $(MAKE)

.PHONY: clean
clean:
	cd $(SRC_DIR) && $(MAKE) clean
	cd $(LIB_DIR) && $(MAKE) clean
	$(RM) $(BIN_DIR)/$(BIN)