lib_names := address_book.so input_handling.so
INC_DIR := ../inc
BLD_DIR := ../build
SRC_DIR := ../src

OBJ := $(lib_names:%.so=$(BLD_DIR)/%.o)

lib_names := $(lib_names:%.so=lib%.so)

.PHONY: all
all: $(lib_names)

$(lib_names):lib%.so : $(BLD_DIR)/%.o
	$(CC) -shared -o $@ $<

$(OBJ):
	cd $(SRC_DIR) && $(MAKE)

.PHONY: clean
clean:
	$(RM) $(lib_names)
