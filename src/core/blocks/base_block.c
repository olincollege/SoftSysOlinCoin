#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "base_block.h"

unsigned char *ser_blockheader(unsigned char *dest, BlockHeader *block_header){
  memcpy(dest, &(block_header->timestamp), sizeof(block_header->timestamp));

  unsigned char *all_tx = dest + sizeof(block_header->timestamp);
  memcpy(all_tx, &(block_header->all_tx), sizeof(block_header->all_tx));

  unsigned char *prev_header_hash = all_tx + sizeof(block_header->all_tx);
  memcpy(prev_header_hash, &(block_header->prev_header_hash), sizeof(block_header->prev_header_hash));

  unsigned char *nonce = prev_header_hash + sizeof(block_header->prev_header_hash);
  memcpy(nonce, &(block_header->nonce), sizeof(block_header->nonce));

  unsigned char* terminate = nonce+sizeof(block_header->nonce);
  return terminate;
}

unsigned char *ser_blockheader_alloc(BlockHeader *block_header){
  unsigned char *data = malloc(sizeof(BlockHeader));
  ser_blockheader(data, block_header);
  return data;
}

void hash_blockheader(BlockHeader *header, unsigned char *buf) {
  unsigned char *header_buf;
  header_buf = ser_blockheader_alloc(header);
  hash_sha256(buf, header_buf, sizeof(BlockHeader));
  free(header_buf);
}

int size_block(Block *block){
  int size = (sizeof(block->num_txs) + sizeof(block->header));
  for(int i = 0; i < block->num_txs; i++){
      size += size_tx(&(block->txs[i]));
  }
  return size;
}

unsigned char *ser_block(unsigned char *dest, Block *block){
  memcpy(dest, &(block->num_txs), sizeof(block->num_txs));

  unsigned char *block_header = dest + sizeof(block->num_txs);
  unsigned char *txs = ser_blockheader(block_header, &(block->header));

  for(int i = 0; i < block->num_txs; i++){
      unsigned char *txs = ser_tx(txs, &(block->txs[i]));
  }
  unsigned char *end = txs;
  return end;
}

unsigned char *ser_block_alloc(Block *block){
  unsigned char *data = malloc(size_block(block));
  ser_block(data, block);
  return data;
}
