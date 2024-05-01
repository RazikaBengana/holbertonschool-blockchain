CC = gcc
CFLAGS = -Wall -Werror -Wextra -pedantic -I.

# Define the directories containing the header files
INCLUDES = -I. -Itransaction

# Source files for blockchain
SRC = blockchain_create.c blockchain_deserialize.c blockchain_destroy.c \
      blockchain_difficulty.c blockchain_serialize.c block_create.c \
      block_destroy.c block_hash.c block_is_valid.c block_mine.c \
      hash_matches_difficulty.c \
      transaction/coinbase_create.c transaction/coinbase_is_valid.c \
      transaction/transaction_create.c transaction/transaction_destroy.c \
      transaction/transaction_hash.c transaction/transaction_is_valid.c \
      transaction/tx_in_create.c transaction/tx_in_sign.c \
      transaction/tx_out_create.c transaction/unspent_tx_out_create.c \
      transaction/update_unspent.c

# Object files corresponding to source files
OBJ = $(SRC:.c=.o)

# Library to build
LIB = libhblk_blockchain.a

all: $(LIB)

# Rule to make the library
$(LIB): $(OBJ)
	ar rcs $@ $^

# Rule to compile source files into object files
%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# Clean target to remove generated files
clean:
	rm -f $(OBJ) $(LIB)

.PHONY: all clean
