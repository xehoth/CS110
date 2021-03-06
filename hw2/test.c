#define CHECK_LIST
#include "doubll2d.h"
#include <stdio.h>
#include <stdlib.h>

void print_list(doubll2d *list) {
  doubll2d_elem *row = list->head, *col = list->head, *last = NULL;
  printf("row = %ld, col = %ld\n", list->dim_row, list->dim_col);
  for (; row; row = row->down) {
    for (col = row; col; last = col, col = col->right) {
      printf("%d ", *(int *)col->data);
    }
    printf("\n");
  }
  if (list->tail != last) printf("tail error\n");
}

bool cmp_less(const doubll2d_elem *a, const doubll2d_elem *b) {
  return *(int *)a->data < *(int *)b->data;
}

int main() {
  {
    doubll2d *list = malloc(sizeof(doubll2d));
    doubll2d_init(list);
    doubll2d_get_head(list);
    doubll2d_get_tail(list);
    doubll2d_dim_col(list);
    doubll2d_dim_col(list);
    print_list(list);
    {
      void *data[1];
      size_t size[1] = {4};
      int a = 12345;
      data[0] = &a;
      doubll2d_insert_row(list, list->head, (void **)&data, size, 1);
    }
    print_list(list);
    {
      void *data[1];
      size_t size[1] = {4};
      int a = 233;
      data[0] = &a;
      doubll2d_insert_col(list, list->head, (void **)&data, size, 1);
    }
    print_list(list);
    {
      void *data[2];
      size_t size[2] = {4, 4};
      int a = 235, b = 236;
      data[0] = &a;
      data[1] = &b;
      doubll2d_insert_row(list, list->head, (void **)&data, size, 2);
    }
    print_list(list);
    {
      void *data[2];
      size_t size[2] = {4, 4};
      int a = 237, b = 238;
      data[0] = &a;
      data[1] = &b;
      doubll2d_insert_col(list, list->head->down->right, (void **)&data, size, 2);
    }
    print_list(list);
    {
      void *data[3];
      size_t size[] = {4, 4, 4};
      int a = 239, b = 240, c = 241;
      data[0] = &a;
      data[1] = &b;
      data[2] = &c;
      doubll2d_insert_row(list, list->head->down->right, (void **)&data, size, 3);
    }
    print_list(list);
    doubll2d_delete_row(list, list->tail->left->up);
    print_list(list);
    printf("min: %d\n", *(int *)doubll2d_find_min(list, cmp_less)->data);
    printf("max: %d\n", *(int *)doubll2d_find_max(list, cmp_less)->data);
    doubll2d_purge(list);
    free(list);
  }
  return 0;
}