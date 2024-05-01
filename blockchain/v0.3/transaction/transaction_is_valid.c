#include "transaction.h"

/**
 * find_unspent_output - program that searches for and returns an unspent
 * transaction output (UTXO) that matches a given transaction input
 *
 * @all_unspent: the list of all UTXOs
 * @in: the transaction input for which to find a matching UTXO
 *
 * Return: the matching UTXO if found, otherwise NULL
 */

unspent_tx_out_t *find_unspent_output(llist_t *all_unspent, tx_in_t *in)
{
	int i, size;
	unspent_tx_out_t *tmp_unspent;

	size = llist_size(all_unspent);

	for (i = 0; i < size; i++)
	{
		tmp_unspent = llist_get_node_at(all_unspent, i);

		if (!memcmp(tmp_unspent->out.hash, in->tx_out_hash, SHA256_DIGEST_LENGTH) &&
		    !memcmp(tmp_unspent->block_hash, in->block_hash, SHA256_DIGEST_LENGTH))
		{
			return (tmp_unspent);
		}
	}
	return (NULL);
}



/**
 * verify_transaction_inputs - program that verifies all transaction inputs
 *
 * @transaction: the transaction whose inputs to verify
 * @all_unspent: the list of all unspent transaction outputs
 *
 * Return: the total amount of the verified inputs,
 *         or 0 if any input is invalid
 */

uint32_t verify_transaction_inputs(transaction_t const *transaction,
				   llist_t *all_unspent)
{
	uint32_t unspent_total = 0;
	tx_in_t *input;
	unspent_tx_out_t *unspent_output;
	int i;

	for (i = 0; i < llist_size(transaction->inputs); i++)
	{
		input = llist_get_node_at(transaction->inputs, i);
		unspent_output = find_unspent_output(all_unspent, input);

		if (!unspent_output || !ec_verify(ec_from_pub(unspent_output->out.pub),
						  transaction->id, SHA256_DIGEST_LENGTH, &input->sig))
		{
			return (0);
		}
		unspent_total += unspent_output->out.amount;
	}

	return (unspent_total);
}



/**
 * transaction_is_valid - program that determines if a transaction is valid
 * by verifying its inputs, ensuring the transaction hash matches,
 * and checking that the total input amount equals the total output amount
 *
 * @transaction: the transaction to validate
 * @all_unspent: the list of all unspent transaction outputs to consider
 *
 * Return: 1 if the transaction is valid, 0 otherwise
 */

int transaction_is_valid(transaction_t const *transaction,
			 llist_t *all_unspent)
{
	uint8_t hash_buf[SHA256_DIGEST_LENGTH];
	uint32_t unspent_total = 0, total = 0;
	int i;

	if (!transaction)
		return (0);

	if (!transaction_hash(transaction, hash_buf) ||
	memcmp(hash_buf, transaction->id, SHA256_DIGEST_LENGTH))
		return (0);

	unspent_total = verify_transaction_inputs(transaction, all_unspent);

	if (unspent_total == 0)
		return (0);

	for (i = 0; i < llist_size(transaction->outputs); i++)
	{
		total += ((tx_out_t *)llist_get_node_at(transaction->outputs, i))->amount;
	}

	return (total == unspent_total);
}
