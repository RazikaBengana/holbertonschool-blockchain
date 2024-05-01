#include "transaction.h"

/**
 * choose_unspent - program that selects unspent transaction outputs
 *
 * @node: the current unspent transaction output node being processed
 * @i: the index of the current node (unused)
 * @args: arguments including the sender's public key, the list of inputs,
 *        and the total amount collected
 *
 * Return: 0 on success, or 1 on failure
 */

int choose_unspent(llist_node_t node, unsigned int i, void *args)
{
	unspent_tx_out_t *unspent = node;
	void **ptr = args;
	tx_in_t *input_tx;
	llist_t *inputs = ptr[1];
	uint32_t *total_amount = ptr[2];

	(void)i;

	if (!memcmp(unspent->out.pub, ptr[0], EC_PUB_LEN))
	{
		input_tx = tx_in_create(unspent);
		llist_add_node(inputs, input_tx, ADD_NODE_REAR);
		*total_amount += unspent->out.amount;
	}
	return (0);
}



/**
 * sign_input_transaction - program that signs the current transaction input
 *
 * @node: the current transaction input node being processed
 * @i: the index of the current node, unused
 * @args: arguments including the transaction id,
 *        the sender's private key, and the all_unspent list
 *
 * Return: 0 on success, or 1 on failure
 */

int sign_input_transaction(llist_node_t node, unsigned int i, void *args)
{
	void **ptr = args;
	tx_in_t *tx_input = node;

	(void)i;

	if (!tx_in_sign(tx_input, ptr[0], ptr[1], ptr[2]))
	{
		fprintf(stderr, "sign_input_transaction: tx_in_sign failed\n");
		return (1);
	}

	return (0);
}



/**
 * generate_outputs - program that creates transaction outputs
 *
 * @sender: the public key of the sender
 * @receiver: the public key of the receiver
 * @amount: the amount to be sent
 * @total: the total amount available to send
 *
 * Return: a list of transaction outputs on success, or NULL on failure
 */

llist_t *generate_outputs(EC_KEY const *sender, EC_KEY const *receiver,
			  uint32_t amount, uint32_t total)
{
	llist_t *outputs;
	tx_out_t *tx_out;
	uint8_t pub[EC_PUB_LEN];

	ec_to_pub(receiver, pub);

	tx_out = tx_out_create(amount, pub);

	if (!tx_out)
	{
		fprintf(stderr, "generate_outputs: tx_out_create failed\n");
		return (NULL);
	}

	outputs = llist_create(MT_SUPPORT_FALSE);

	llist_add_node(outputs, tx_out, ADD_NODE_REAR);

	if (total > amount)
	{
		fprintf(stderr, "sending change...\n");
		ec_to_pub(sender, pub);
		tx_out = tx_out_create(total - amount, pub);
		if (!tx_out)
		{
			fprintf(stderr, "generate_outputs: tx_out_create fail\n");
			return (NULL);
		}

		llist_add_node(outputs, tx_out, ADD_NODE_REAR);
	}

	fprintf(stderr, "generate_outputs: success\n");

	return (outputs);
}



/**
 * transaction_create - program that creates a new transaction
 *
 * this function prepares a new transaction from a sender to a receiver
 * for a specified amount using available unspent transaction outputs;
 * it gathers enough unspent transactions to cover the amount, creates
 * the necessary transaction inputs, and signs them;
 * it also generates transaction outputs to send the specified amount
 * to the receiver and returns the change to the sender
 *
 * @sender: the EC public key of the sender
 * @receiver: the EC public key of the receiver
 * @amount: the amount to be transferred in the transaction
 * @all_unspent: a list of all unspent transaction outputs available for use
 *
 * Return: a pointer to a newly created transaction on success,
 *         or NULL on failure
 */

transaction_t *transaction_create(EC_KEY const *sender, EC_KEY const *receiver,
				  uint32_t amount, llist_t *all_unspent)
{
	uint8_t sender_pub[EC_PUB_LEN];
	uint32_t unspent = 0;
	transaction_t *tx;
	llist_t *tx_in, *tx_out;
	void *args[3];

	if (!sender || !receiver || !all_unspent)
		return (NULL);

	tx = calloc(1, sizeof(*tx));

	if (!tx)
		return (NULL);

	tx_in = llist_create(MT_SUPPORT_FALSE);
	ec_to_pub(sender, sender_pub);
	args[0] = sender_pub, args[1] = tx_in, args[2] = &unspent;
	llist_for_each(all_unspent, choose_unspent, args);

	if (unspent < amount)
	{
		fprintf(stderr, "transaction_create: insufficient funds\n");
		llist_destroy(tx_in, 1, NULL);
		free(tx);
		return (NULL);
	}

	tx_out = generate_outputs(sender, receiver, amount, unspent);

	if (!tx_out)
	{
		llist_destroy(tx_in, 1, NULL);
		free(tx);
		return (NULL);
	}
	tx->inputs = tx_in, tx->outputs = tx_out;

	transaction_hash(tx, tx->id);
	args[0] = tx->id, args[1] = (void *)sender, args[2] = all_unspent;
	llist_for_each(tx->inputs, sign_input_transaction, args);

	return (tx);
}
