#include "blockchain.h"

/**
 * validate_header - program that validates the header of a blockchain file
 *
 * @hdr: a pointer to the header structure to validate
 *
 * Return: 1 if the header is valid, 0 otherwise
 */

int validate_header(block_header_t *hdr)
{
	if (memcmp(hdr->magic, "HBLK", 4) != 0 ||
	    memcmp(hdr->version, "0.3", 3) != 0)
	{
		return (0);  /* Header is invalid */
	}
	return (1);  /* Header is valid */
}



/**
 * load_transactions - program that reads transactions from a file
 * and stores them in a block
 *
 * @blk: a pointer to the block where transactions will be stored
 * @file: the file pointer from which to read the transactions
 *
 * Return: nothing (void)
 */

void load_transactions(block_t *blk, FILE *file)
{
	int i, j, inCount, outCount, transCount;
	transaction_t *trans;
	tx_in_t *input;
	tx_out_t *output;

	fread(&transCount, 4, 1, file);

	if (transCount == -1)
	{
		blk->transactions = NULL;
		return;
	}
	blk->transactions = llist_create(MT_SUPPORT_FALSE);

	for (i = 0; i < transCount; i++)
	{
		trans = malloc(sizeof(transaction_t));
		fread(trans, 32, 1, file);
		fread(&inCount, 4, 1, file);
		fread(&outCount, 4, 1, file);
		trans->inputs = llist_create(MT_SUPPORT_FALSE);

		for (j = 0; j < inCount; j++)
		{
			input = malloc(sizeof(tx_in_t));
			fread(input, 169, 1, file);
			llist_add_node(trans->inputs, input, ADD_NODE_REAR);
		}
		trans->outputs = llist_create(MT_SUPPORT_FALSE);

		for (j = 0; j < outCount; j++)
		{
			output = malloc(sizeof(tx_out_t));
			fread(output, 101, 1, file);
			llist_add_node(trans->outputs, output, ADD_NODE_REAR);
		}
		llist_add_node(blk->transactions, trans, ADD_NODE_REAR);
	}
}



/**
 * blockchain_deserialize - program that deserializes a blockchain from a file
 *
 * @path: the path to the file from which to load the blockchain
 *
 * Return: a pointer to the loaded blockchain, or NULL on failure
 */

blockchain_t *blockchain_deserialize(char const *path)
{
	FILE *file = NULL;
	uint32_t i;
	block_t *blk;
	block_header_t hdr;
	blockchain_t *chain;
	unspent_tx_out_t *utxo;

	file = fopen(path, "rb");

	if (!file)
		return (NULL);

	fread(&hdr, sizeof(hdr), 1, file);

	if (!validate_header(&hdr))
		return (NULL);

	if (hdr.blocks == 0)
	{
		fclose(file);
		return (NULL);
	}

	chain = malloc(sizeof(blockchain_t));
	chain->chain = llist_create(MT_SUPPORT_FALSE);
	chain->unspent = llist_create(MT_SUPPORT_FALSE);

	for (i = 0; i < hdr.blocks; i++)
	{
		blk = malloc(sizeof(block_t));
		fread(blk, sizeof(block_info_t), 1, file);
		fread(&blk->data.len, 4, 1, file);
		memset(blk->data.buffer, 0, sizeof(blk->data.buffer));
		fread(blk->data.buffer, blk->data.len, 1, file);
		fread(blk->hash, sizeof(blk->hash), 1, file);
		load_transactions(blk, file);
		llist_add_node(chain->chain, blk, ADD_NODE_REAR);
	}
	for (i = 0; i < hdr.unspent; i++)
	{
		utxo = malloc(sizeof(unspent_tx_out_t));
		fread(utxo, 165, 1, file);
		llist_add_node(chain->unspent, utxo, ADD_NODE_REAR);
	}
	fclose(file);

	return (chain);
}