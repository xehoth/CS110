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
#define ALIGNED(x) __attribute__ ((aligned(x)))
#define L1_CACHE_LINE 64

static int any_find_flag;

typedef struct ALIGNED(L1_CACHE_LINE) _thread_data {
  blkh_t ALIGNED(L1_CACHE_LINE) header;
  unsigned char hash_buf[HASH_BLOCK_SIZE];
  unsigned char one_diff[HASH_BLOCK_SIZE];
  int diff_q;
  int diff_m;
  int find_flag;
  int id;
  hash_func *hash_func;
} ThreadData;

ThreadData threadData[THREAD_NUMS];

void *mine_work_thread(void *thData) {
  ThreadData *data = (ThreadData *)thData;
  data->header.nonce = data->id;
  for (;;) {
    blockchain_node_hash((blk_t *)data, data->hash_buf, data->hash_func);
    if (any_find_flag || ((!memcmp(data->hash_buf, data->one_diff, sizeof(unsigned char) * data->diff_q)) &&
        memcmp(&data->hash_buf[data->diff_q], &data->one_diff[data->diff_q],
               sizeof(unsigned char) * (HASH_BLOCK_SIZE - data->diff_q)) <= 0)) {
      data->find_flag = 1;
      any_find_flag = 1;
      break;
    }
    data->header.nonce += THREAD_NUMS;
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
  
  any_find_flag = 0;
  
  for (i = 0; i < THREAD_NUMS; ++i) {
    memcpy(&threadData[i].header, &node->header, sizeof(blkh_t));
    threadData[i].diff_q = diff / 8;
    threadData[i].diff_m = diff % 8;
    memset(threadData[i].one_diff, 0xFF, sizeof(unsigned char) * HASH_BLOCK_SIZE);
    memset(threadData[i].one_diff, 0, sizeof(unsigned char) * threadData[i].diff_q);
    threadData[i].one_diff[threadData[i].diff_q] = ((uint8_t)0xFF) >> threadData[i].diff_m;
    threadData[i].find_flag = 0;
    threadData[i].id = i;
    threadData[i].hash_func = func;
    pthread_create(&threads[i], NULL, mine_work_thread, (void *)&threadData[i]);
  }
  for (i = 0; i < THREAD_NUMS; ++i) pthread_join(threads[i], NULL);
  for (i = 0; i < THREAD_NUMS; ++i) {
    if (threadData[i].find_flag) {
      node->header.nonce = threadData[i].header.nonce;
      memcpy(node->hash, threadData[i].hash_buf, sizeof(unsigned char) * HASH_BLOCK_SIZE);
      break;
    }
  }
  (void)hash_buf;
#endif
}

#ifdef MULTI_THREAD
#undef THREAD_NUMS
#endif