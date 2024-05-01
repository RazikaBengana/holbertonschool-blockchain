CC = gcc
CFLAGS = -Wall -Werror -Wextra -pedantic -I.

SRC = blockchain_create.c blockchain_deserialize.c blockchain_destroy.c \
      blockchain_difficulty.c blockchain_serialize.c block_create.c \
      block_destroy.c block_hash.c block_is_valid.c block_mine.c \
      hash_matches_difficulty.c

OBJ = $(SRC:.c=.o)

LIB = libhblk_blockchain_v0.2.a

all: $(LIB)

$(LIB): $(OBJ)
	ar rcs $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(LIB)

.PHONY: all clean