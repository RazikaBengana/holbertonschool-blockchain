#ifndef BLOCKCHAIN_H
#define BLOCKCHAIN_H


#include <llist.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <time.h>
#include <openssl/sha.h>
#include "./provided/endianness.h"
#include "../../crypto/hblk_crypto.h"
#include "transaction/transaction.h"


#define GENESIS_HASH "\xc5\x2c\x26\xc8\xb5\x46\x16\x39\x63\x5d\x8e\xdf\x2a\x97\xd4\x8d\x0c\x8e\x00\x09\xc8\x17\xf2\xb1\xd3\xd7\xff\x2f\x04\x51\x58\x03"


#define true 1
#define false 0

#define GENESIS_DATA "Holberton School"
#define GENESIS_TIME 1537578000
#define HBLK_MAGIC "HBLK"
#define HBLK_VERSION "0.3"
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
	}, \
	NULL, /* transactions */ \
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
 * @chain:   Linked list of Blocks
 * @unspent: Linked list of unspent transaction outputs
 */

typedef struct blockchain_s
{
    llist_t     *chain;
    llist_t     *unspent;
} blockchain_t;



/**
 * struct block_s - Block structure
 *
 * @info:         Block info
 * @data:         Block data
 * @transactions: List of transactions
 * @hash:         256-bit digest of the Block, to ensure authenticity
 */

typedef struct block_s
{
    block_info_t    info; /* This must stay first */
    block_data_t    data; /* This must stay second */
    llist_t     *transactions;
    uint8_t     hash[SHA256_DIGEST_LENGTH];
} block_t;



/**
 * struct block_header_s - Structure used for blockchain I/O
 * operations
 *
 * @magic:    A 4-byte field that identifies the file as a valid blockchain data file
 * @version:  A 3-byte field representing the version of the blockchain format
 * @endian:   A single byte indicating the byte order;
 *            '1' for little endian, '2' for big endian
 * @blocks:   Number of blocks in blockchain
 * @unspent:  Number of unspent transactions in the blockchain
 */

typedef struct block_header_s
{
    unsigned char magic[4];
    unsigned char version[3];
    unsigned char endian;
    uint32_t blocks;
    uint32_t unspent;
} block_header_t;



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
int blockchain_serialize(blockchain_t const *blockchain, char const *path);

/* blockchain_deserialize.c */
blockchain_t *blockchain_deserialize(char const *path);

/* block_is_valid.c */
int block_is_valid(block_t const *block, block_t const *prev_block,
		   llist_t *all_unspent);

/* hash_matches_difficulty.c */
int hash_matches_difficulty(uint8_t const hash[SHA256_DIGEST_LENGTH],
			    uint32_t difficulty);

/* block_mine.c */
void block_mine(block_t *block);

/* blockchain_difficulty.c */
uint32_t blockchain_difficulty(blockchain_t const *blockchain);



#endif /* BLOCKCHAIN_H */