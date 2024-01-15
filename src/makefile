lib_names := address_book.so

SRC := $(shell find -name '*.c' -not -name '$(lib_names:%.so=%.c)')
OBJ := $(SRC:%.c=%.o)
INC_DIR := ../inc
BLD_DIR := ../build
CFLAGS := -Wall -Wextra -std=c99 -g

OBJ := $(OBJ:%.o=$(BLD_DIR)/%.o)

.PHONY: all
all: $(OBJ)

$(OBJ): $(BLD_DIR)/%.o: %.c
	mkdir -p $(BLD_DIR)
	$(CC) -I$(INC_DIR) -c $(CFLAGS) $< -o $@

.PHONY: clean
clean:
	$(RM) $(OBJ)