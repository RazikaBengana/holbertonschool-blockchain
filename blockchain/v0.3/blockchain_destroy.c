#include "blockchain.h"

/**
 * blockchain_destroy - program that safely frees all memory
 * associated with a blockchain
 *
 * this function checks if the provided blockchain pointer is not NULL,
 * then proceeds to destroy and free all linked lists within the blockchain
 * structure (such as blocks and unspent transactions), and finally frees
 * the blockchain structure itself;
 * this helps prevent memory leaks
 *
 * @blockchain: a pointer to the blockchain structure to be destroyed
 *
 * Return: nothing (void)
 */

void blockchain_destroy(blockchain_t *blockchain)
{
	if (blockchain == NULL)
	{
		return;
	}
	llist_destroy(blockchain->chain, 1, (node_dtor_t)block_destroy);
	llist_destroy(blockchain->unspent, 1, NULL);

	free(blockchain);
}
