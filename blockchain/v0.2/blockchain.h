#ifndef BLOCKCHAIN_H
#define BLOCKCHAIN_H


#include <llist.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <time.h>
#include <fcntl.h>
#include <unistd.h>
#include <openssl/sha.h>
#include "./provided/endianness.h"
#include "../../crypto/hblk_crypto.h"


#define GENESIS_HASH "\xc5\x2c\x26\xc8\xb5\x46\x16\x39\x63\x5d\x8e\xdf\x2a\x97\xd4\x8d\x0c\x8e\x00\x09\xc8\x17\xf2\xb1\xd3\xd7\xff\x2f\x04\x51\x58\x03"


#define true 1
#define false 0
#define GENESIS_DATA "Holberton School"
#define GENESIS_TIME 1537578000
#define HBLK_MAGIC "HBLK"
#define HBLK_VERSION "0.2"
#define LSB 1
#define MSB 2
#define HBLK_ENDIAN LSB


#define BLOCKCHAIN_DATA_MAX 1024


#define GENESIS_BLOCK { \
	{ /* info */ \
		0 /* index */, \
		0, /* difficulty */ \
		1537578000, /* timestamp */ \
		0, /* nonce */ \
		{0} /* prev_hash */ \
	}, \
	{ /* data */ \
		"Holberton School", /* buffer */ \
		16 /* len */ \
	}, /* hashed data */\
	"\xc5\x2c\x26\xc8\xb5\x46\x16\x39\x63\x5d\x8e\xdf\x2a\x97\xd4\x8d" \
	"\x0c\x8e\x00\x09\xc8\x17\xf2\xb1\xd3\xd7\xff\x2f\x04\x51\x58\x03" \
}


#define SHA256_DIGEST_LENGTH 32
#define BLOCK_GENERATION_INTERVAL 1
#define DIFFICULTY_ADJUSTMENT_INTERVAL 5



/**
 * struct block_info_s - Block info structure
 *
 * @index:      Index of the Block in the Blockchain
 * @difficulty: Difficulty of proof of work (hash leading zero bits)
 * @timestamp:  Time the Block was created at (UNIX timestamp)
 * @nonce:      Salt value used to alter the Block hash
 * @prev_hash:  Hash of the previous Block in the Blockchain
 */

typedef struct block_info_s
{
    /*
     * The order of the elements in this structure should remain the same.
     * It was designed so every element of this structure is aligned and
     * doesn't require padding from the compiler.
     * Therefore, it is possible to use the structure as an array of char,
     * on any architecture.
     */

    uint32_t    index;
    uint32_t    difficulty;
    uint64_t    timestamp;
    uint64_t    nonce;
    uint8_t     prev_hash[SHA256_DIGEST_LENGTH];
} block_info_t;



/**
 * struct block_data_s - Block data
 *
 * @buffer: Data buffer
 * @len:    Data size (in bytes)
 */

typedef struct block_data_s
{
    /*
     * @buffer must stay first, so we can directly use the structure as
     * an array of char
     */

    int8_t      buffer[BLOCKCHAIN_DATA_MAX];
    uint32_t    len;
} block_data_t;



/**
 * struct blockchain_s - Blockchain structure
 *
 * @chain: Linked list of pointers to block_t
 */

typedef struct blockchain_s
{
    llist_t     *chain;
} blockchain_t;



/**
 * struct block_s - Block structure
 *
 * @info: Block info
 * @data: Block data
 * @hash: 256-bit digest of the Block, to ensure authenticity
 */

typedef struct block_s
{
    block_info_t    info; /* This must stay first */
    block_data_t    data; /* This must stay second */
    uint8_t     hash[SHA256_DIGEST_LENGTH];
} block_t;



/* blockchain_create.c */
blockchain_t *blockchain_create(void);

/* block_create.c */
block_t *block_create(block_t const *prev, int8_t const *data,
		      uint32_t data_len);

/* block_destroy.c */
void block_destroy(block_t *block);

/* blockchain_destroy.c */
void blockchain_destroy(blockchain_t *blockchain);

/* block_hash.c */
uint8_t *block_hash(block_t const *block,
		    uint8_t hash_buf[SHA256_DIGEST_LENGTH]);

/* blockchain_serialize.c */
int write_block_to_file(llist_node_t node, unsigned int idx, void *arg);
int blockchain_serialize(blockchain_t const *blockchain, char const *path);

/* blockchain_deserialize.c */
void byteSwap(uint8_t *bytesPtr, size_t byteCount);
int deserialize_attr(int fileDescriptor, int encodingFlag,
		     void *attributePtr, size_t attributeSize);
int init_blockchain_from_file(const char *filePath, blockchain_t **blockchain,
			      uint8_t *encodingFlag, int *fileDescriptor);
int read_blocks_into_blockchain(int fileDescriptor, uint8_t encodingFlag,
				blockchain_t *blockchain);
blockchain_t *blockchain_deserialize(char const *path);

/* block_is_valid.c */
int block_is_valid(block_t const *block, block_t const *prev_block);

/* hash_matches_difficulty.c */
int hash_matches_difficulty(uint8_t const hash[SHA256_DIGEST_LENGTH],
			    uint32_t difficulty);

/* block_mine.c */
void block_mine(block_t *block);

/* blockchain_difficulty.c */
uint32_t blockchain_difficulty(blockchain_t const *blockchain);



#endif /* BLOCKCHAIN_H */
