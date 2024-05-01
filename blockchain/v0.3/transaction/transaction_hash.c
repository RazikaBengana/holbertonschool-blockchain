#include "transaction.h"

/**
 * copy_hashes - program that copies a specified number of hashes
 * from a source to a destination buffer
 *
 * this function is intended to simplify the process of copying
 * multiple hashes in a row, adjusting the pointer in the destination
 * buffer as it goes
 *
 * @ptr: a pointer to the current position in the destination buffer;
 *       this pointer will be advanced by the number of bytes copied
 * @source: the source buffer from which to copy hashes
 * @n: the number of hashes to copy from the source to the destination
 *
 * Return: nothing (void)
 */

void copy_hashes(uint8_t **ptr, const uint8_t *source, size_t n)
{
	memcpy(*ptr, source, SHA256_DIGEST_LENGTH * n);
	*ptr += SHA256_DIGEST_LENGTH * n;
}



/**
 * transaction_hash - program that computes the hash (ID) of a transaction
 * and stores it in a provided buffer
 *
 * the function aggregates the hashes of all transaction inputs and outputs,
 * concatenates them into a single buffer, and then computes the hash of
 * this buffer;
 * the computed hash is intended to serve as a unique identifier for
 * the transaction
 *
 * @transaction: a pointer to the transaction to compute the hash of
 * @hash_buf: the buffer in which to store the computed hash
 *
 * Return: a pointer to 'hash_buf', containing the computed hash
 *         if successful, or NULL otherwise
 */

uint8_t *transaction_hash(transaction_t const *transaction,
			  uint8_t hash_buf[SHA256_DIGEST_LENGTH])
{
	size_t tx_in_size = llist_size(transaction->inputs) *
		(SHA256_DIGEST_LENGTH * 3);
	size_t tx_out_size = llist_size(transaction->outputs) * SHA256_DIGEST_LENGTH;
	size_t total_size = tx_in_size + tx_out_size;
	uint8_t *buffer = malloc(total_size), *ptr = buffer;
	int i;
	tx_in_t *input;
	tx_out_t *output;

	if (!transaction || !hash_buf)
		return (NULL);

	if (!buffer)
		return (NULL);

	for (i = 0; i < llist_size(transaction->inputs); i++)
	{
		input = llist_get_node_at(transaction->inputs, i);

		copy_hashes(&ptr, input->block_hash, 1);
		copy_hashes(&ptr, input->tx_id, 1);
		copy_hashes(&ptr, input->tx_out_hash, 1);
	}

	for (i = 0; i < llist_size(transaction->outputs); i++)
	{
		output = llist_get_node_at(transaction->outputs, i);

		copy_hashes(&ptr, output->hash, 1);
	}

	sha256((const int8_t *)buffer, total_size, hash_buf);

	free(buffer);

	return (hash_buf);
}
