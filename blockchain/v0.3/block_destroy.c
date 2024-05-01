#include "blockchain.h"

/**
 * block_destroy - program that deletes an existing block and frees
 * its allocated memory
 *
 * this function safely deallocates a block, including
 * its transactions list, and then the block itself;
 * it ensures all associated memory is released to prevent leaks
 *
 * @block: a pointer to the block to delete
 *
 * Return: nothing (void)
 */

void block_destroy(block_t *block)
{
	if (!block)
		return;

	llist_destroy(block->transactions, 1, (node_dtor_t)transaction_destroy);

	free(block);
}
