#include "transaction.h"

/**
 * unspent_tx_out_create - program that creates a new unspent transaction
 * output
 *
 * @block_hash: the hash of the Block containing the transaction
 * @tx_id: the ID of the transaction containing the output
 * @out: a pointer to the transaction output
 *
 * Return: a pointer to the created unspent transaction output upon success,
 *         or NULL upon failure
 */

unspent_tx_out_t *unspent_tx_out_create(
	uint8_t block_hash[SHA256_DIGEST_LENGTH],
	uint8_t tx_id[SHA256_DIGEST_LENGTH],
	tx_out_t const *out)
{
	unspent_tx_out_t *unspent_tx_out = malloc(sizeof(unspent_tx_out_t));

	if (!unspent_tx_out)
	{
		return (NULL);
	}

	memcpy(unspent_tx_out->block_hash, block_hash, SHA256_DIGEST_LENGTH);
	memcpy(unspent_tx_out->tx_id, tx_id, SHA256_DIGEST_LENGTH);
	memcpy(&unspent_tx_out->out, out, sizeof(tx_out_t));

	return (unspent_tx_out);
}
