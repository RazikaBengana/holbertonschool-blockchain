#include "blockchain.h"

/**
 * init_blockchain_structure - program that initializes the blockchain
 * structure
 *
 * this function allocates memory for the blockchain and creates linked lists
 * for managing blocks and unspent transaction outputs (UTXOs);
 * the chain list holds all the blocks in the blockchain, while the unspent
 * list tracks all UTXOs for managing cryptocurrency ownership
 *
 * Return: a pointer to the newly initialized blockchain structure,
 *         or NULL if an error occurs during allocation or list creation
 */

blockchain_t *init_blockchain_structure(void)
{
	blockchain_t *blockchain = malloc(sizeof(*blockchain));

	if (!blockchain)
	{
		return (NULL);
	}

	blockchain->chain = llist_create(MT_SUPPORT_FALSE);
	blockchain->unspent = llist_create(MT_SUPPORT_FALSE);

	if (!blockchain->chain || !blockchain->unspent)
	{
		free(blockchain);

		blockchain = (NULL);
	}

	return (blockchain);
}



/**
 * add_genesis_block - program that creates and adds the genesis block
 * to the blockchain
 *
 * the genesis block is the first block in the blockchain with predefined
 * values;
 * this block starts the blockchain
 *
 * @blockchain: a pointer to the blockchain instance to which
 *              the genesis block will be added
 *
 * Return: 0 on successful addition of the genesis block,
 *         or -1 if an error occurs
 */

int add_genesis_block(blockchain_t *blockchain)
{
	block_t *genesis_block = malloc(sizeof(*genesis_block));

	if (!genesis_block)
	{
		return (-1);
	}

	memset(genesis_block, 0, sizeof(*genesis_block));

	genesis_block->info.index = 0;
	genesis_block->info.difficulty = 0;
	genesis_block->info.timestamp = 1537578000;
	genesis_block->info.nonce = 0;

	memset(genesis_block->info.prev_hash, 0, SHA256_DIGEST_LENGTH);

	strncpy((char *)genesis_block->data.buffer, "Holberton School",
		BLOCKCHAIN_DATA_MAX);

	genesis_block->data.len = 16;

	memcpy(genesis_block->hash, GENESIS_HASH, SHA256_DIGEST_LENGTH);

	if (llist_add_node(blockchain->chain, genesis_block, ADD_NODE_FRONT) != 0)
	{
		free(genesis_block);
		return (-1);
	}

	return (0);
}



/**
 * blockchain_create - program that creates a new blockchain instance,
 * initializing it with a genesis block
 *
 * this function serves as the entry point for creating a blockchain;
 * it first initializes the blockchain structure, including the lists
 * for managing blocks and UTXOs;
 * then, it adds the genesis block to the blockchain
 *
 * Return: a pointer to the newly created blockchain if successful,
 *         otherwise NULL
 */

blockchain_t *blockchain_create(void)
{
	blockchain_t *blockchain = init_blockchain_structure();

	if (!blockchain || !blockchain->chain || !blockchain->unspent)
	{
		if (blockchain)
		{
			llist_destroy(blockchain->chain, 1, NULL);
			llist_destroy(blockchain->unspent, 1, NULL);
			free(blockchain);
		}
		return (NULL);
	}

	if (add_genesis_block(blockchain) != 0)
	{
		llist_destroy(blockchain->chain, 1, NULL);
		llist_destroy(blockchain->unspent, 1, NULL);

		free(blockchain);

		return (NULL);
	}

	return (blockchain);
}
