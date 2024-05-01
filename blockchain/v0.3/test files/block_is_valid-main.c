#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "../blockchain.h"

void _blockchain_print_brief(blockchain_t const *blockchain);
void _print_hex_buffer(uint8_t const *buf, size_t len);

/**
 * _add_block - Adds a new block to the blockchain with specified data and mines it
 *
 * this function creates a new block with the specified data
 * and a coinbase transaction created for the miner;
 * it then attempts to mine the block;
 * if the block is valid, it is added to the blockchain;
 * otherwise, an error is logged
 *
 * @blockchain: Pointer to the blockchain to which the block will be added
 * @prev: Pointer to the previous block in the blockchain
 * @data: Data to be stored in the new block
 * @miner: EC_KEY pointer representing the miner's public key
 *
 * Return: Pointer to the newly added block
 */

static block_t *_add_block(blockchain_t *blockchain, block_t const *prev,
			   char const *data, EC_KEY *miner)
{
	block_t *block;
	transaction_t *coinbase;

	block = block_create(prev, (int8_t *)data, (uint32_t)strlen(data));
	block->info.difficulty = 20;

	coinbase = coinbase_create(miner, block->info.index);
	llist_add_node(block->transactions, coinbase, ADD_NODE_FRONT);

	block_mine(block);

	if (block_is_valid(block, prev, blockchain->unspent) == 0)
	{
		printf("Block mined: [%u] ", block->info.difficulty);
		_print_hex_buffer(block->hash, SHA256_DIGEST_LENGTH);
		printf("\n");
		llist_add_node(blockchain->chain, block, ADD_NODE_REAR);
	}
	else
	{
		fprintf(stderr, "Invalid Block with index: %u\n",
			block->info.index);
	}

	return (block);
}



/**
 * main - Entry point
 *
 * Return: EXIT_SUCCESS or EXIT_FAILURE
 */

int main(void)
{
	blockchain_t *blockchain;
	block_t *block;
	EC_KEY *miner;

	miner = ec_create();
	blockchain = blockchain_create();

	block = llist_get_head(blockchain->chain);
	block = _add_block(blockchain, block, "Holberton", miner);
	block = _add_block(blockchain, block, "School", miner);

	blockchain_destroy(blockchain);
	EC_KEY_free(miner);

	return (EXIT_SUCCESS);
}