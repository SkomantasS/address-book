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

.PHONY: install
install:$(BIN_DIR)/$(BIN)
	cp -f $(LIB_DIR)/lib$(lib_names).so /usr/lib

.PHONY: uninstall
uninstall:
	rm -f /usr/lib/lib$(lib_names).so

.PHONY: clean
clean:
	cd $(SRC_DIR) && $(MAKE) clean
	cd $(LIB_DIR) && $(MAKE) clean
	$(RM) $(BIN_DIR)/$(BIN)
