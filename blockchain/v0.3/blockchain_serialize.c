#include "blockchain.h"

/**
 * initialize_header - program that initializes the header
 * for blockchain serialization with default values
 *
 * @header: a pointer to the header structure to be initialized
 *
 * Return: nothing (void)
 */

void initialize_header(block_header_t *header)
{
	const char default_magic[] = {'H', 'B', 'L', 'K'};
	const char default_version[] = {'0', '.', '3'};

	memcpy(header->magic, default_magic, sizeof(default_magic));
	memcpy(header->version, default_version, sizeof(default_version));

	header->endian = 1;
	header->blocks = 0;
	header->unspent = 0;
}



/**
 * serialize_transactions - program that writes all transactions
 * of a blockchain block to a file
 *
 * @transactions: the list of transactions to write
 * @file: a pointer to the file where transactions will be written
 *
 * Return: nothing (void)
 */

void serialize_transactions(llist_t *transactions, FILE *file)
{
	int tx_count, input_count, output_count, total_inputs, total_outputs;
	transaction_t *transaction;
	tx_in_t *input;
	tx_out_t *output;

	for (tx_count = 0; tx_count < llist_size(transactions); tx_count++)
	{
		transaction = llist_get_node_at(transactions, tx_count);
		total_inputs = llist_size(transaction->inputs);
		total_outputs = llist_size(transaction->outputs);

		fwrite(transaction, 1, 32, file);
		fwrite(&total_inputs, 1, 4, file);
		fwrite(&total_outputs, 1, 4, file);

		for (input_count = 0; input_count < total_inputs; input_count++)
		{
			input = llist_get_node_at(transaction->inputs, input_count);
			fwrite(input, 1, 169, file);
		}
		for (output_count = 0; output_count < total_outputs; output_count++)
		{
			output = llist_get_node_at(transaction->outputs, output_count);
			fwrite(output, 1, 101, file);
		}
	}
}



/**
 * blockchain_serialize - program that serializes a blockchain into a file
 *
 * @blockchain: a pointer to the blockchain to serialize
 * @path: the file path where the blockchain will be saved
 *
 * Return: 0 on success, -1 on failure
 */

int blockchain_serialize(blockchain_t const *blockchain, char const *path)
{
	FILE *file = NULL;
	uint32_t block_idx;
	int transaction_size;
	block_t *block;
	unspent_tx_out_t *unspent_tx;
	block_header_t header;

	initialize_header(&header);
	header.blocks = llist_size(blockchain->chain);
	header.unspent = llist_size(blockchain->unspent);

	file = fopen(path, "wb");

	if (!file)
		return (-1);

	fwrite(&header, 1, sizeof(header), file);

	for (block_idx = 0; block_idx < header.blocks; block_idx++)
	{
		block = llist_get_node_at(blockchain->chain, block_idx);
		fwrite(block, 1, 56, file);
		fwrite(&block->data.len, 1, 4, file);
		fwrite(block->data.buffer, 1, block->data.len, file);
		fwrite(block->hash, 1, 32, file);
		transaction_size = block->info.index ==
				   0 ? -1 : llist_size(block->transactions);
		fwrite(&transaction_size, 1, 4, file);
		serialize_transactions(block->transactions, file);
	}
	for (block_idx = 0; block_idx < header.unspent; block_idx++)
	{
		unspent_tx = llist_get_node_at(blockchain->unspent, block_idx);
		fwrite(unspent_tx, 1, 165, file);
	}
	fclose(file);

	return (0);
}