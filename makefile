BIN := address_book_program
CFLAGS := -Wall -Wextra -std=c99 -g
SCR := $(shell find -name '*.c')
OBJ := $(SCR:%.c=%.o)

.PHONY: all
all: $(BIN)

$(BIN):$(OBJ)
	$(CC) $^ -o $@

$(OBJ):%.o: %.c
	$(CC) -c $(CFLAGS) $< -o $@

.PHONY: clean
clean:
	$(RM) $(OBJ) $(BIN)