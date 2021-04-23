#include <x86intrin.h>
#include <stdint.h>
#include <stdio.h>
#include <pthread.h>

uint64_t rdtsc(){
  return __rdtsc();
}

#define THS 10

typedef struct _thread_data {
  int id;
  int sum;
} ThreadData;

ThreadData data[THS];
int test;

void *work(void *thData) {
  pthread_exit(NULL);
}

int main() {
  int i;
  uint64_t start, end;
  pthread_t threads[THS];
  start = rdtsc();
  for (i = 0; i < THS; ++i) pthread_create(&threads[i], NULL, work, (void *)&data[i]);
  for (i = 0; i < THS; ++i) pthread_join(threads[i], NULL);
  end = rdtsc();
  printf("cpu time: %lu\n", end - start);
  return 0;
}