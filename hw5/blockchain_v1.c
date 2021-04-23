/*********************************************************************
Homework 5
CS 110: Computer Architecture, Spring 2021
ShanghaiTech University

* Last Modified: 03/28/2021
*********************************************************************/

#include "blockchain.h"
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <stdio.h>

void blockchain_node_init(blk_t *node, uint32_t index, uint32_t timestamp,
                          unsigned char prev_hash[32], unsigned char *data,
                          size_t data_size) {
  if (!node || !data || !prev_hash)
    return;

  node->header.index = index;
  node->header.timestamp = timestamp;
  node->header.nonce = -1;

  memset(node->header.data, 0, sizeof(unsigned char) * 256);
  memcpy(node->header.prev_hash, prev_hash, HASH_BLOCK_SIZE);
  memcpy(node->header.data, data,
         sizeof(unsigned char) * ((data_size < 256) ? data_size : 256));
}

void blockchain_node_hash(blk_t *node, unsigned char hash_buf[HASH_BLOCK_SIZE],
                          hash_func func) {
  if (node)
    func((unsigned char *)node, sizeof(blkh_t), (unsigned char *)hash_buf);
}

BOOL blockchain_node_verify(blk_t *node, blk_t *prev_node, hash_func func) {
  unsigned char hash_buf[HASH_BLOCK_SIZE];

  if (!node || !prev_node)
    return False;

  blockchain_node_hash(node, hash_buf, func);
  if (memcmp(node->hash, hash_buf, sizeof(unsigned char) * HASH_BLOCK_SIZE))
    return False;

  blockchain_node_hash(prev_node, hash_buf, func);
  if (memcmp(node->header.prev_hash, hash_buf,
             sizeof(unsigned char) * HASH_BLOCK_SIZE))
    return False;

  return True;
}

#define MULTI_THREAD
#ifdef MULTI_THREAD
#define THREAD_NUMS 2

static uint64_t bonce_buffer[THREAD_NUMS];
static unsigned char one_diff_thread_buffer[HASH_BLOCK_SIZE];
static unsigned char hash_buf_thread[THREAD_NUMS][HASH_BLOCK_SIZE];
static int find_flag_thread[THREAD_NUMS];
static int any_find_flag;
static int diff_q_thread;
static int diff_m_thread;
static hash_func *hash_func_thread;
typedef struct _thread_data {
  blkh_t header;
  int id;
} ThreadData;

void *mine_work_thread(void *data) {
  const int id = ((ThreadData *)data)->id;
  bonce_buffer[id] = id;
  for (;;) {
    blockchain_node_hash((blk_t *)data, hash_buf_thread[id], hash_func_thread);
    if (any_find_flag || ((!memcmp(hash_buf_thread[id], one_diff_thread_buffer, sizeof(unsigned char) * diff_q_thread)) &&
        memcmp(&hash_buf_thread[id][diff_q_thread], &one_diff_thread_buffer[diff_q_thread],
               sizeof(unsigned char) * (HASH_BLOCK_SIZE - diff_q_thread)) <= 0)) {
      find_flag_thread[id] = 1;
      any_find_flag = 1;
      break;
    }
    ((blkh_t *)data)->nonce += THREAD_NUMS;
  }
  pthread_exit(NULL);
}
#endif

/* The sequiental implementation of mining implemented for you. */
void blockchain_node_mine(blk_t *node, unsigned char hash_buf[HASH_BLOCK_SIZE],
                          size_t diff, hash_func func) {
#ifndef MULTI_THREAD
  unsigned char one_diff[HASH_BLOCK_SIZE];
  size_t diff_q, diff_m;
  diff_q = diff / 8;
  diff_m = diff % 8;
  memset(one_diff, 0xFF, sizeof(unsigned char) * HASH_BLOCK_SIZE);
  memset(one_diff, 0, sizeof(unsigned char) * diff_q);
  one_diff[diff_q] = ((uint8_t)0xFF) >> diff_m;

  while (True) {
    blockchain_node_hash(node, hash_buf, func);
    if ((!memcmp(hash_buf, one_diff, sizeof(unsigned char) * diff_q)) &&
        memcmp(&hash_buf[diff_q], &one_diff[diff_q],
               sizeof(unsigned char) * (HASH_BLOCK_SIZE - diff_q)) <= 0) {

      memcpy(node->hash, hash_buf, sizeof(unsigned char) * HASH_BLOCK_SIZE);
      break;
    }
    node->header.nonce++;
  }
#else
  int i;
  pthread_t threads[THREAD_NUMS];
  ThreadData threadData[THREAD_NUMS];
  diff_q_thread = diff / 8;
  diff_m_thread = diff % 8;
  memset(one_diff_thread_buffer, 0xFF, sizeof(unsigned char) * HASH_BLOCK_SIZE);
  memset(one_diff_thread_buffer, 0, sizeof(unsigned char) * diff_q_thread);
  one_diff_thread_buffer[diff_q_thread] = ((uint8_t)0xFF) >> diff_m_thread;
  any_find_flag = 0;
  hash_func_thread = func;
  memset(find_flag_thread, 0, sizeof(find_flag_thread));
  for (i = 0; i < THREAD_NUMS; ++i) {
    memcpy(&threadData[i].header, &node->header, sizeof(blkh_t));
    threadData[i].id = i;
    pthread_create(&threads[i], NULL, mine_work_thread, (void *)&threadData[i]);
  }
  for (i = 0; i < THREAD_NUMS; ++i) pthread_join(threads[i], NULL);
  for (i = 0; i < THREAD_NUMS; ++i) {
    if (find_flag_thread[i]) {
      node->header.nonce = threadData[i].header.nonce;
      memcpy(node->hash, hash_buf_thread[i], sizeof(unsigned char) * HASH_BLOCK_SIZE);
      break;
    }
  }
  (void)hash_buf;
#endif
}

#ifdef MULTI_THREAD
#undef THREAD_NUMS
#endif