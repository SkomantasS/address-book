CFLAGS := -Wall -Wextra -std=c99 -g
SCR := $(shell find -name '*.c')
OBJ := $(SCR:%.c=%.o)

all: address_book_program
.PHONY: all

address_book_program:$(OBJ)
	cc $(OBJ) -o $@

$(OBJ):%.o: %.c
	cc -c $(CFLAGS) $< -o $@

.PHONY: clean
clean:
	rm -f *.o