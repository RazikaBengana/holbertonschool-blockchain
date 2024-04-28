#include "blockchain.h"

/**
 * byteSwap - program that performs byte swapping on an array of bytes
 * in place
 *
 * this is typically used for converting between endianesses
 *
 * @bytesPtr: a pointer to the array of bytes to swap
 * @byteCount: the number of bytes in the array
 *
 * Return: nothing (void)
 */

void byteSwap(uint8_t *bytesPtr, size_t byteCount)
{
	uint8_t buffer[64] = {0};
	int index;

	for (index = byteCount - 1; index >= 0; index--)
		buffer[byteCount - index - 1] = bytesPtr[index];

	for (index = 0; index < (int)byteCount; index++)
		bytesPtr[index] = buffer[index];
}




/**
 * deserialize_attr - program that reads an attribute from a file descriptor
 * and optionally performs byte swapping
 *
 * this function is used for reading data with specific encoding from a file
 *
 * @fileDescriptor: the file descriptor to read from
 * @encodingFlag: indicates the encoding of the data (like MSB for big-endian)
 * @attributePtr: a pointer to a buffer where the read data will be stored
 * @attributeSize: the number of bytes to read
 *
 * Return: 1 if successful, 0 otherwise
 */

int deserialize_attr(int fileDescriptor, int encodingFlag,
		     void *attributePtr, size_t attributeSize)
{
	if (read(fileDescriptor, attributePtr,
		 attributeSize) != (ssize_t)attributeSize)
		return (0);

	if (encodingFlag == MSB)
		byteSwap((uint8_t *)attributePtr, attributeSize);

	return (1);
}




/**
 * init_blockchain_from_file - program that initializes a blockchain
 * from a file
 *
 * this function initializes a blockchain from a file by checking
 * the magic number and version, and then setting up the initial
 * blockchain structure in memory
 *
 * @filePath: the path to the blockchain file to deserialize
 * @blockchain: a pointer to the blockchain structure to be filled
 * @encodingFlag: a pointer to the encoding flag to be set based on
 *                the file's encoding
 * @fileDescriptor: a pointer to the file descriptor to be used for reading
 *
 * Return: 1 on success, 0 on failure
 */

int init_blockchain_from_file(const char *filePath, blockchain_t **blockchain,
			      uint8_t *encodingFlag, int *fileDescriptor)
{
	unsigned char buffer[sizeof(block_t)];

	*fileDescriptor = open(filePath, O_RDONLY);

	if (*fileDescriptor == -1)
		return (0);

	if (read(*fileDescriptor, buffer, sizeof(HBLK_MAGIC) - 1) <
	    (ssize_t)sizeof(HBLK_MAGIC) - 1 ||
		     memcmp(buffer, HBLK_MAGIC, sizeof(HBLK_MAGIC) - 1))
	{
		close(*fileDescriptor);
		return (0);
	}

	if (read(*fileDescriptor, buffer, sizeof(HBLK_VERSION) - 1) <
	    (ssize_t)sizeof(HBLK_VERSION) - 1)
	{
		close(*fileDescriptor);
		return (0);
	}

	*blockchain = blockchain_create();

	if (!*blockchain)
	{
		close(*fileDescriptor);
		return (0);
	}

	block_destroy((block_t *)llist_pop((*blockchain)->chain));

	read(*fileDescriptor, encodingFlag, sizeof(*encodingFlag));

	return (1);
}




/**
 * read_blocks_into_blockchain - program that reads each block from the file
 * and adds it to the blockchain
 *
 * this function includes deserializing each block's attributes and adding
 * them to the blockchain structure
 *
 * @fileDescriptor: the file descriptor for reading the file
 * @encodingFlag: the encoding flag indicating the data's endianess
 * @blockchain: the blockchain to which the blocks will be added
 *
 * Return: 1 on success, 0 on failure
 */

int read_blocks_into_blockchain(int fileDescriptor, uint8_t encodingFlag,
				blockchain_t *blockchain)
{
	uint32_t blockCount = 0;
	block_t *block = NULL;

	deserialize_attr(fileDescriptor, encodingFlag, &blockCount,
			 sizeof(blockCount));

	while (blockCount--)
	{
		block = calloc(1, sizeof(block_t));

		if (!deserialize_attr(fileDescriptor, encodingFlag,
				      &block->info.index, sizeof(block->info.index)) ||
		    !deserialize_attr(fileDescriptor, encodingFlag,
				      &block->info.difficulty, sizeof(block->info.difficulty)) ||
		    !deserialize_attr(fileDescriptor, encodingFlag,
				      &block->info.timestamp, sizeof(block->info.timestamp)) ||
		    !deserialize_attr(fileDescriptor, encodingFlag,
				      &block->info.nonce, sizeof(block->info.nonce)) ||
		    !deserialize_attr(fileDescriptor, encodingFlag,
				      block->info.prev_hash, sizeof(block->info.prev_hash)) ||
		    !deserialize_attr(fileDescriptor, encodingFlag,
				      &block->data.len, sizeof(block->data.len)) ||
		    !deserialize_attr(fileDescriptor, encodingFlag,
				      block->data.buffer, block->data.len) ||
		    !deserialize_attr(fileDescriptor, encodingFlag,
				      block->hash, sizeof(block->hash))) {
			llist_destroy(blockchain->chain, true, (node_dtor_t)block_destroy);

			free(blockchain);

			close(fileDescriptor);

			return (0);
		}
		llist_add_node(blockchain->chain, block, ADD_NODE_REAR);
	}
	return (1);
}




/**
 * blockchain_deserialize - program that deserializes a blockchain from
 * a file, creating a blockchain structure in memory
 *
 * this function opens a file, checks for correct blockchain magic and
 * version numbers, then reads each block into the blockchain structure,
 * performing byte swaps as necessary
 *
 * @filePath: the path to the blockchain file to deserialize
 *
 * Return: a pointer to the deserialized blockchain,
 *         or NULL if an error occurs
 */

blockchain_t *blockchain_deserialize(char const *filePath)
{
	int fileDescriptor = 0;
	uint8_t encodingFlag = 0;
	blockchain_t *blockchain = NULL;

	if (!init_blockchain_from_file(filePath, &blockchain, &encodingFlag,
				       &fileDescriptor))
	{
		return (NULL);
	}

	if (!read_blocks_into_blockchain(fileDescriptor, encodingFlag, blockchain))
	{
		llist_destroy(blockchain->chain, true, (node_dtor_t)block_destroy);
		free(blockchain);
		blockchain = NULL;
	}

	close(fileDescriptor);

	return (blockchain);
}

