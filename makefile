BIN := address_book_program
CFLAGS := -Wall -Wextra -std=c99 -g

BIN_DIR := ./bin
BLD_DIR := ./build
INC_DIR := ./inc
LIB_DIR := ./lib
PWD := $(shell pwd)
SRC_DIR := ./src

lib_name := address_book

.PHONY: all
all:$(BIN)

$(BIN):builddeps
	mkdir -p $(BIN_DIR)
	$(CC) -Wl,-rpath=$(PWD)/$(LIB_DIR) $(CFLAGS) -I$(INC_DIR) -L$(LIB_DIR) $(BLD_DIR)/*.o -l$(lib_name) -o $(BIN_DIR)/$@

.PHONY: builddeps
builddeps:
	cd $(SRC_DIR) && $(MAKE)
	cd $(LIB_DIR) && $(MAKE)


.PHONY: clean
clean:
	cd $(SRC_DIR) && $(MAKE) clean
	cd $(LIB_DIR) && $(MAKE) clean
	$(RM) $(BIN_DIR)/$(BIN)