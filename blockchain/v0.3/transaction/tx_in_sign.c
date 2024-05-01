#include "transaction.h"

/**
 * tx_in_sign - program that signs a transaction input
 *
 * this function verifies the public key derived from the sender's
 * private key matches the public key stored in the transaction
 * output referenced by the transaction input to be signed;
 * it then signs the transaction ID using the sender's private key
 *
 * @in: a pointer to the transaction input structure to sign
 * @tx_id: contains the ID (hash) of the transaction the input is stored in
 * @sender: contains the private key of the receiver of the coins
 * @all_unspent: a list of all unspent transaction outputs to date
 *
 * Return: a pointer to the resulting signature structure upon success,
 *         or NULL on failure
 */

sig_t *tx_in_sign(tx_in_t *in, uint8_t const tx_id[SHA256_DIGEST_LENGTH],
		  EC_KEY const *sender, llist_t *all_unspent)
{
	uint8_t pub[EC_PUB_LEN];
	unspent_tx_out_t *unspent;
	ssize_t i;

	for (i = 0; i < llist_size(all_unspent); i++)
	{
		unspent = llist_get_node_at(all_unspent, i);

		if (!memcmp(in->tx_out_hash, unspent->out.hash, SHA256_DIGEST_LENGTH))
		{
			break;
		}
		unspent = NULL;
	}

	if (!unspent || !ec_to_pub(sender, pub) ||
	memcmp(pub, unspent->out.pub, EC_PUB_LEN))
	{
		return (NULL);
	}

	if (!ec_sign(sender, tx_id, SHA256_DIGEST_LENGTH, &(in->sig)))
	{
		return (NULL);
	}

	return (&(in->sig));
}
