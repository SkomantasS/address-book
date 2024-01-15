lib_names := address_book.so #input_handling.so
INC_DIR := ../inc
BLD_DIR := ../build

.PHONY: all
all: $(lib_names)
	
$(lib_names):
	$(CC) -shared -o lib$@ $(BLD_DIR)/$(@:%.so=%.o)

.PHONY: clean
clean:
	$(RM) $(lib_names:%=lib%)
