#include "transaction.h"

/**
 * transaction_destroy - program that frees a transaction
 * and all its associated data
 *
 * @transaction: a pointer to the transaction structure to be freed
 *
 * Return: nothing (void)
 */

void transaction_destroy(transaction_t *transaction)
{
	if (!transaction)
		return;

	llist_destroy(transaction->inputs, 1, free);
	llist_destroy(transaction->outputs, 1, free);

	free(transaction);
}
