/*********************************************************************
Homework 5
CS 110: Computer Architecture, Spring 2021
ShanghaiTech University

* Last Modified: 03/28/2021
*********************************************************************/

#include "blockchain.h"
#include "hash_function.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <x86intrin.h>

uint64_t rdtsc(){
  return __rdtsc();
}


#define DELIMIT()                                                              \
  printf("-------------------------------------------------------------------" \
         "-----------\n");

#define TIME_SPENT(tstart, tend) (((double)(tend - tstart)) / CLOCKS_PER_SEC)

/******************************************************************************
 * Hexdump function shamelessly stealed from
 * https://gist.github.com/richinseattle/c527a3acb6f152796a580401057c78b4    */
#include <ctype.h>

#ifndef HEXDUMP_COLS
#define HEXDUMP_COLS 16
#endif

static void hexdump(void *mem, unsigned int len) {
  unsigned int i, j;

  for (i = 0;
       i <
       len + ((len % HEXDUMP_COLS) ? (HEXDUMP_COLS - len % HEXDUMP_COLS) : 0);
       i++) {
    /* print offset */
    if (i % HEXDUMP_COLS == 0) {
      printf("0x%06x: ", i);
    }

    /* print hex data */
    if (i < len) {
      printf("%02x ", 0xFF & ((char *)mem)[i]);
    } else {
      printf("   ");
    }

    /* print ASCII dump */
    if (i % HEXDUMP_COLS == (HEXDUMP_COLS - 1)) {
      for (j = i - (HEXDUMP_COLS - 1); j <= i; j++) {
        if (j >= len) {
          putchar(' ');
        } else if (isprint(((char *)mem)[j])) {
          putchar(0xFF & ((char *)mem)[j]);
        } else {
          putchar('.');
        }
      }
      putchar('\n');
    }
  }
}
/* Hexdump function from
 * https://gist.github.com/richinseattle/c527a3acb6f152796a580401057c78b4 ends.
 *****************************************************************************/

/* Hexdump helpers that help you debug. */

/* Hexdump a variable `var` with `len` bytes. */
#define HEXDUMP_VAR(var, len)                                                  \
  printf("Content of `%s`, %ld bytes:\n", #var, len);                          \
  hexdump((void *)var, len);

/* Hexdump all attributes in a `blk_t` node. */
#define HEXDUMP_NODE(blk_node_ptr)                                             \
  printf("Dumping the content of `%s`:\n", #blk_node_ptr);                     \
  HEXDUMP_VAR(blk_node_ptr.header.index, sizeof(uint32_t));                    \
  HEXDUMP_VAR(blk_node_ptr.header.timestamp, sizeof(uint32_t));                \
  HEXDUMP_VAR(blk_node_ptr.header.prev_hash,                                   \
              HASH_BLOCK_SIZE * sizeof(unsigned char))                         \
  HEXDUMP_VAR(blk_node_ptr.header.data, 256 * sizeof(unsigned char));          \
  HEXDUMP_VAR(blk_node_ptr.header.nonce, sizeof(uint64_t));                    \
  HEXDUMP_VAR(blk_node_ptr.hash, HASH_BLOCK_SIZE * sizeof(unsigned char));

int main(int argc, char *argv[]) {
  blk_t blk_node;
  blk_t prev_blk_node;
  unsigned char hash_buff[HASH_BLOCK_SIZE];
  int diff = 1;
  clock_t tstart, tend;

  /* stdout is buffered by default on most systems, we disable it. */
  setvbuf(stdout, NULL, _IONBF, 0);

  printf("Test your implementation here.\n");
  DELIMIT();

  printf(
      "A simple test case for testing your implementation on two blocks:\n\n");

  /* The test takes an integer argument indicating the difficulty... */
  if (argc == 2) {
    diff = strtol(argv[1], NULL, 10);
    if (diff >= 64)
      diff = 1;
  } else
    diff = 1;

  printf("Initalizing nodes to be tested... ");
  memset(hash_buff, 0, sizeof(unsigned char) * HASH_BLOCK_SIZE);
  blockchain_node_init(&prev_blk_node, 1, 1, (unsigned char *)hash_buff,
                       (unsigned char *)"hello world!", sizeof("hello world!"));
  blockchain_node_hash(&prev_blk_node, ((unsigned char *)(&prev_blk_node.hash)),
                       blockchain_do_hash);
  blockchain_node_init(
      &blk_node, 2, 1, ((unsigned char *)(&prev_blk_node.hash)),
      (unsigned char *)"good bye, world.", sizeof("good bye, world."));
  printf("Done.\n");

  printf("Mining a block with difficulty %d... ", diff);
  tstart = rdtsc();
  blockchain_node_mine(&blk_node, (unsigned char *)hash_buff, diff,
                       blockchain_do_hash);
  tend = rdtsc();
  printf("cpu clock %f\n", TIME_SPENT(tstart, tend));

  printf("Testing if the block is good... ");
  if (blockchain_node_verify(&blk_node, &prev_blk_node, blockchain_do_hash))
    printf("Good.\n");
  else {
    printf("Not good.\n");
    printf("Showing content of the nodes:\n");
    DELIMIT();
    HEXDUMP_NODE(&blk_node);
    DELIMIT();
    HEXDUMP_NODE(&prev_blk_node);
    DELIMIT();
    return 1;
  }

  DELIMIT();
  return 0;
}
