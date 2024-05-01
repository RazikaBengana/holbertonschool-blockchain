#include "blockchain.h"

/**
 * validate_transactions - program that validates all transactions in a block
 *
 * @block: a pointer to the block containing transactions to be validated
 * @all_unspent: a pointer to all unspent transaction outputs (UTXOs)
 *
 * Return: 0 if all transactions are valid, 1 otherwise
 */

int validate_transactions(block_t const *block, llist_t *all_unspent)
{
	int i;
	transaction_t *tx;

	if (llist_size(block->transactions) == 0)
		return (1); /* Block must contain at least one transaction */

	for (i = 0; i < llist_size(block->transactions); i++)
	{
		tx = llist_get_node_at(block->transactions, i);

		if (i == 0 && !coinbase_is_valid(tx, block->info.index))
			return (1); /* First transaction must be a valid coinbase transaction */

		if (i > 0 && !transaction_is_valid(tx, all_unspent))
			return (1); /* All subsequent transactions must be valid */
	}

	return (0); /* All transactions are valid */
}



/**
 * block_is_valid - program that validates a block within a blockchain
 * context, incorporating checks for transaction validity
 *
 * this function examines a block to ensure it meets the blockchain's validity
 * criteria, including verifying its relationship with the previous block,
 * its index, the integrity of its hash values, whether its hash matches
 * the expected difficulty level, and the validity of all contained
 * transactions against a list of unspent transaction outputs (UTXOs)
 *
 * @block: a pointer to the block to be validated;
 *         should not be NULL except for the genesis block,
 *         which is the first block in the chain
 * @prev_block: a pointer to the block immediately preceding the current block
 *              in the blockchain;
 *              this should be NULL if and only if the block being validated
 *              is the genesis block
 * @all_unspent: a pointer to all unspent transaction outputs (UTXOs),
 *               used to validate transactions
 *
 * Return: 0 if the block is valid according to the blockchain's criteria,
 *         1 if the block is invalid, if any of the validation checks fail,
 *         or if any parameters are incorrectly provided (such as a NULL
 *         block pointer when not validating the genesis block)
 */

int block_is_valid(block_t const *block, block_t const *prev_block,
		   llist_t *all_unspent)
{
	uint8_t hash[SHA256_DIGEST_LENGTH] = {0};
	block_t const tmp = GENESIS_BLOCK;

	if (!block || (!prev_block && block->info.index != 0) || !all_unspent)
		return (1);

	if (block->info.index == 0)
		return (memcmp(block, &tmp, sizeof(tmp)));

	if (block->info.index != prev_block->info.index + 1)
		return (1);

	if (!block_hash(prev_block, hash) ||
	memcmp(hash, prev_block->hash, SHA256_DIGEST_LENGTH))
		return (1);

	if (memcmp(prev_block->hash, block->info.prev_hash, SHA256_DIGEST_LENGTH))
		return (1);

	if (!block_hash(block, hash) ||
	memcmp(hash, block->hash, SHA256_DIGEST_LENGTH))
		return (1);

	if (block->data.len > BLOCKCHAIN_DATA_MAX)
		return (1);

	if (!hash_matches_difficulty(block->hash, block->info.difficulty))
		return (1);

	/* Validate transactions */
	if (validate_transactions(block, all_unspent) != 0)
		return (1);

	return (0); /* Block is valid */
}
