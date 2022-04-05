#pragma once

#include "constants.h"
#include "uthash.h"
#include "base_block.h"
#include "constants.h"

typedef struct BlockChain {
  unsigned char id[BLOCK_HASH_LEN];
  Block *block;
  UT_hash_handle hh;
} BlockChain;

BlockChain *blockchain;
unsigned char top_block_header_hash[BLOCK_HASH_LEN];
unsigned long chain_height;

/* Initializes the global blockchain variable */
void blockchain_init();

/* Creates a new entry in the hashmap with the passed block
 *
 * Returns passed block pointer if entry created, NULL otherwise
 *
 * block: Block pointer that will be stored in entry
 */
Block *blockchain_add(Block *block);

/* Removes the entry corresponding to header_hash
 *
 * Returns the block pointer stored in removed entry if succesfully removed,
 * NULL otherwise
 *
 * header_hash: Buffer of length BLOCK_HASH_LEN, hash of block header
 */
Block *blockchain_remove(unsigned char *header_hash);

/* Finds block corresponding to header_hash
 *
 * Returns block pointer if found, NULL otherwise
 *
 * header_hash: Buffer of length BLOCK_HASH_LEN, hash of block header
 */
Block *blockchain_find(unsigned char *header_hash);


/* Finds entry corresponding to header_hash
 *
 * Returns entry if found, NULL otherwise
 *
 * header_hash: Buffer of length BLOCK_HASH_LEN, hash of block header
 */
BlockChain *blockchain_find_node(unsigned char *header_hash);

/*
Prints a single hashmap entry to stdout

prefix: string to put in front of all print commands used for tabbing structure
*/
void print_blockchain(BlockChain *blockchain_node, char *prefix);
void pretty_print_blockchain(BlockChain *blockchain_node, char *prefix);

/*
Prints the entire blockchain Hashmap to stdout

prefix: string to put in front of all print commands used for tabbing structure
*/
void print_blockchain_hashmap(char *prefix);
void pretty_print_blockchain_hashmap();

