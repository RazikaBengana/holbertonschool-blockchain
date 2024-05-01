#include "transaction.h"

/**
 * unspent_find - program that searches for an unspent transaction
 * output (UTXO) in a linked list
 *
 * @node: a node in the list of UTXOs
 * @hash: the hash of the transaction to find
 *
 * Return: 1 if the UTXO with the given hash is found, 0 otherwise
 */

int unspent_find(llist_node_t node, void *hash)
{
	unspent_tx_out_t *utx = node;

	return (!memcmp(utx->out.hash, hash, SHA256_DIGEST_LENGTH));
}



/**
 * update_unspent - program that updates the list of all unspent transaction
 * outputs (UTXOs) based on the current block transactions
 *
 * this function removes the spent transactions from the list of UTXOs
 * and adds new UTXOs
 *
 * @transactions: the list of transactions to process
 * @block_hash: the hash of the current block
 * @all_unspent: the list of all unspent transactions to update
 *
 * Return: the updated list of all unspent transactions
 */

llist_t *update_unspent(llist_t *transactions,
			uint8_t block_hash[SHA256_DIGEST_LENGTH],
			llist_t *all_unspent)
{
	transaction_t *tx;
	tx_out_t *txo;
	tx_in_t *txi;
	unspent_tx_out_t *utx;
	int i, j;

	if (!transactions || !block_hash || !all_unspent)
		return (NULL);

	for (i = 0; i < llist_size(transactions); i++)
	{
		tx = llist_get_node_at(transactions, i);

		for (j = 0; j < llist_size(tx->inputs); j++)
		{
			txi = llist_get_node_at(tx->inputs, j);

			llist_remove_node(all_unspent, unspent_find,
					  txi->tx_out_hash, 1, free);
		}

		for (j = 0; j < llist_size(tx->outputs); j++)
		{
			txo = llist_get_node_at(tx->outputs, j);
			utx = unspent_tx_out_create(block_hash, tx->id, txo);

			llist_add_node(all_unspent, utx, ADD_NODE_REAR);
		}
	}
	return (all_unspent);
}