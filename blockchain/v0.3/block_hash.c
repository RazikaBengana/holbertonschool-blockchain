#include "blockchain.h"

/**
 * block_hash - program that computes the SHA-256 hash of a given block's
 * contents, including its transactions
 *
 * @block: a pointer to the block to be hashed;
 *         this includes both its metadata, data, and transactions
 * @hash_buf: a buffer where the resulting SHA-256 hash will be stored;
 *            this buffer must be at least SHA256_DIGEST_LENGTH bytes long
 *
 * Return: a pointer to the buffer containing the hash if successful,
 *         or NULL if the operation fails due to invalid input parameters
 *         or memory allocation issues
 */

uint8_t *block_hash(block_t const *block,
		    uint8_t hash_buf[SHA256_DIGEST_LENGTH])
{
	size_t data_size;
	size_t offset;
	uint8_t *data_to_hash;
	int i;
	transaction_t *tx;

	if (!block || !hash_buf)
		return (NULL);

	data_size = sizeof(block->info) + block->data.len;

	for (i = 0; i < llist_size(block->transactions); i++)
	{
		tx = llist_get_node_at(block->transactions, i);
		data_size += SHA256_DIGEST_LENGTH;
	}

	data_to_hash = malloc(data_size);

	if (!data_to_hash)
		return (NULL);

	memcpy(data_to_hash, &block->info, sizeof(block->info));
	memcpy(data_to_hash + sizeof(block->info),
	       block->data.buffer, block->data.len);

	offset = sizeof(block->info) + block->data.len;

	for (i = 0; i < llist_size(block->transactions); i++)
	{
		tx = llist_get_node_at(block->transactions, i);
		memcpy(data_to_hash + offset, tx->id, SHA256_DIGEST_LENGTH);
		offset += SHA256_DIGEST_LENGTH;
	}

	SHA256(data_to_hash, data_size, hash_buf);

	free(data_to_hash);

	return (hash_buf);
}
