#include "transaction.h"

/**
 * tx_out_create - program that allocates and initializes
 * a transaction output structure
 *
 * @amount: the amount of the transaction
 * @pub: the public key of the transaction receiver
 *
 * Return: a pointer to the created transaction output upon success,
 *         or NULL upon failure
 */

tx_out_t *tx_out_create(uint32_t amount, uint8_t const pub[EC_PUB_LEN])
{
	tx_out_t *out = malloc(sizeof(tx_out_t));

	if (out == NULL)
	{
		return (NULL);
	}

	out->amount = amount;

	memcpy(out->pub, pub, EC_PUB_LEN);

	if (!sha256((int8_t const *)out, sizeof(uint32_t) + EC_PUB_LEN, out->hash))
	{
		free(out);
		return (NULL);
	}

	return (out);
}
