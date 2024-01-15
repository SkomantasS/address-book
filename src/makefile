SRC := $(shell find -name '*.c')
OBJ := $(SRC:%.c=%.o)
INC_DIR := ../inc
BLD_DIR := ../build
CFLAGS := -Wall -Wextra -std=c99 -g -fPIC

.PHONY: all
all: $(OBJ)

$(OBJ):%.o: %.c
	$(CC) -I$(INC_DIR) -c $(CFLAGS) $< -o $(BLD_DIR)/$@

.PHONY: clean
clean:
	cd $(BLD_DIR) && $(RM) $(OBJ)