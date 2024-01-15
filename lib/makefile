lib_names := address_book.so
INC_DIR := ../inc
BLD_DIR := ../build
SRC_DIR := ../src

CFLAGS := -Wall -Wextra -std=c99 -g -fPIC

OBJ := $(lib_names:%.so=%.o)

lib_names := $(lib_names:%.so=lib%.so)

.PHONY: all
all: $(lib_names)

$(lib_names):lib%.so : %.o
	$(CC) -shared -o $@ $<

$(OBJ):%.o:$(SRC_DIR)/%.c
	$(CC) -I$(INC_DIR) -c $(CFLAGS) $< -o $@

.PHONY: clean
clean:
	$(RM) $(lib_names) $(OBJ)