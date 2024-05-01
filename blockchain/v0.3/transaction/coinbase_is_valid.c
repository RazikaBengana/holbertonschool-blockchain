#include "transaction.h"

/**
 * is_zeroed - program that checks if the specified array is zeroed
 *
 * @arr: a pointer to the array
 * @size: the size of the array in bytes
 *
 * Return: 1 if the array is zeroed, 0 otherwise
 */

int is_zeroed(const uint8_t *arr, size_t size)
{
	size_t i;

	for (i = 0; i < size; ++i)
	{
		if (arr[i] != 0)
			return (0);
	}
	return (1);
}



/**
 * validate_input - program that checks if the transaction input is valid
 *
 * @input: the transaction input to validate
 * @block_index: the index of the block the coinbase transaction belongs to
 *
 * Return: 1 if the input is valid, 0 otherwise
 */

int validate_input(tx_in_t *input, uint32_t block_index)
{
	if (!is_zeroed(input->block_hash, SHA256_DIGEST_LENGTH) ||
	    !is_zeroed(input->tx_id, SHA256_DIGEST_LENGTH) ||
	    !is_zeroed(input->sig.sig, input->sig.len) ||
	    input->sig.len != 0 ||
	    *(uint32_t *)input->tx_out_hash != block_index)
	{
		return (0);
	}
	return (1);
}



/**
 * validate_output - program that checks if the transaction output is valid
 *
 * @output: the transaction output to validate
 * @expected_amount: the expected amount of the output
 *
 * Return: 1 if the output is valid, 0 otherwise
 */

int validate_output(tx_out_t *output, uint32_t expected_amount)
{
	if (output->amount != expected_amount)
	{
		return (0);
	}
	return (1);
}



/**
 * coinbase_is_valid - program that checks if a coinbase transaction is valid
 *
 * @coinbase: points to the coinbase transaction to verify
 * @block_index: the index of the Block the coinbase transaction
 *               will belong to
 *
 * Return: 1 if the coinbase transaction is valid, and 0 otherwise
 */

int coinbase_is_valid(transaction_t const *coinbase, uint32_t block_index)
{
	uint8_t hash_buf[SHA256_DIGEST_LENGTH];
	uint32_t expected_amount = COINBASE_AMOUNT;
	tx_in_t *input;
	tx_out_t *output;

	if (!coinbase || llist_size(coinbase->inputs) != 1 ||
	llist_size(coinbase->outputs) != 1)
	{
		return (0);
	}

	if (!transaction_hash(coinbase, hash_buf) ||
	memcmp(coinbase->id, hash_buf, SHA256_DIGEST_LENGTH) != 0)
	{
		return (0);
	}

	input = llist_get_node_at(coinbase->inputs, 0);
	output = llist_get_node_at(coinbase->outputs, 0);

	if (!validate_input(input, block_index) ||
	!validate_output(output, expected_amount))
	{
		return (0);
	}

	return (1);
}
