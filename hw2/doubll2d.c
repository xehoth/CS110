#include "doubll2d.h"
#include <string.h>
#include <stdlib.h>

/*check whether list is valid*/
static bool is_list_valid(doubll2d *list) {
  /*null pointer*/
  if (!list) return false;
  /*empty list*/
  if (!list->head) return list->tail == NULL && list->dim_col == 0 && list->dim_row == 0;
  /*because head is not null*/
  if (!list->tail) return false;
  if (list->head->left || list->head->up || list->tail->right || list->tail->down) return false;
  return true;
}

/*initialize a 2D doubly linked list*/
void doubll2d_init(doubll2d *list) {
  if (!list) return; /*check if the list is NULL*/
  /*set a empty list, head, tail ---> NULL*/
  list->head = list->tail = NULL;
  /*set to a 0 x 0 list*/
  list->dim_col = list->dim_row = 0;
}

doubll2d_elem *doubll2d_get_head(doubll2d *list) {
  /*check if the list is NULL*/
  if (!is_list_valid(list)) return NULL;
  return list->head;
}

doubll2d_elem *doubll2d_get_tail(doubll2d *list) {
  /*check if the list is NULL*/
  if (!is_list_valid(list)) return NULL;
  return list->tail;
}

size_t doubll2d_dim_row(doubll2d *list) {
  /*check if the list is NULL*/
  if (!is_list_valid(list)) return -1;
  return list->dim_row;
}

size_t doubll2d_dim_col(doubll2d *list) {
  /*check if the list is NULL*/
  if (!is_list_valid(list)) return -1;
  return list->dim_col;
}

#ifdef CHECK_LIST
/*check whether cursor is in the list*/
static bool check_list(doubll2d *list, doubll2d_elem *cursor) {
  doubll2d_elem *row_ptr = NULL, *col_ptr = NULL;
  /*check if the list is NULL*/
  if (!list || !cursor) return false;
  /*loop through row and then use col_ptr loop through col*/
  row_ptr = col_ptr = list->head;
  /*loop through row*/
  for (; row_ptr; row_ptr = row_ptr->down) {
     /*loop through col*/
    for (col_ptr = row_ptr; col_ptr; col_ptr = col_ptr->right) {
      if (cursor == col_ptr) return true;
    }
  }
  /*not found*/
  return false;
}
#endif

static doubll2d_elem *new_list_node(void *data, size_t size) {
  doubll2d_elem *ret = NULL;
  /*check if data is NULL*/
  if (!data) return NULL;
  /*check is ret is NULL*/
  if (!(ret = malloc(sizeof(doubll2d_elem)))) return NULL;
  /*set all ptrs to NULL*/
  ret->left = ret->right = ret->up = ret->down = NULL;
  /*copy the size*/
  ret->size = size;
  /*malloc memory for data*/
  if (!(ret->data = malloc(size))) return NULL;
  /*copy the data*/
  memcpy(ret->data, data, size);
  return ret;
}

/*insert one node below the ptr*/
static doubll2d_elem *insert_down_one(doubll2d *list, doubll2d_elem *ptr, void *data,
                             size_t size) {
  /*create a new node*/
  doubll2d_elem *new_node = new_list_node(data, size), *next = NULL;
  bool is_tail = false;
  /*check whether the new_node is NULL*/
  if (!new_node) return NULL;
  /*check if list tail*/
  is_tail = !ptr->right && !ptr->down;
  /**
   * ptr
   *  ^
   *  |
   *  v
   * next
   */
  next = ptr->down;
  /**
   * new_node
   *   ^
   *   |
   * next
   */
  if (next) next->up = new_node;
  /**
   * new_node
   *   ^
   *   |
   *   v
   * next
   */
  new_node->down = next;
  /**
   *   ptr 
   *    ^
   *    |
   * new_node
   */
  new_node->up = ptr;
  /**
   *   ptr 
   *    ^
   *    |
   *    v
   * new_node
   */
  ptr->down = new_node;
  /*if insert after the tail, set the tail*/
  if (is_tail) list->tail = new_node;
  return new_node;
}

doubll2d_elem *doubll2d_insert_row(doubll2d *list, doubll2d_elem *cursor, void **data,
                          size_t *size, size_t length) {
  /*insert a new row*/
  doubll2d_elem *left_most_ptr = NULL, *prev = NULL, *cur = NULL;
  int now_col = 0;
  /*check if the list is NULL*/
  if (!is_list_valid(list)) return NULL;
  /*check if length is less than dim_row*/
  if (length < doubll2d_dim_col(list)) return NULL;
  /*empty list*/
  if (!list->head) {
    if (data && size && length) {
      /*just create a new node*/
      list->head = list->tail = new_list_node(data[0], size[0]);
      list->dim_col = list->dim_row = 1;
      return list->head;
    }
    /*invalid case*/
    return NULL;
  }
#ifdef CHECK_LIST
  /*do list checking*/
  if (!check_list(list, cursor)) return NULL;
#endif
  if (!cursor || !data || !size) return NULL;
  /*get the left most ptr in this row*/
  left_most_ptr = cursor;
  /*loop to the left most*/
  while (left_most_ptr->left) left_most_ptr = left_most_ptr->left;
  /*from left -> right to insert down each node*/
  for (; left_most_ptr; left_most_ptr = left_most_ptr->right, ++now_col) {
    /*insert one node down*/
    if (!(cur = insert_down_one(list, left_most_ptr, data[now_col], size[now_col])))
      return NULL;
    /**
     * prev <- cur
     */
    cur->left = prev;
    /**
     * prev <-> cur
     */
    if (prev) prev->right = cur;
    /**
     * prev (x) ----- prev (cur)
     */
    prev = cur;
  }
  /*there's new row inserted*/
  ++list->dim_row;
  /*need to return the newly created element below the cursor*/
  return cursor->down;
}

/*insert one node after the ptr*/
static doubll2d_elem *insert_right_one(doubll2d *list, doubll2d_elem *ptr, void *data,
                              size_t size) {
  /*create a new node*/
  doubll2d_elem *new_node = new_list_node(data, size), *next = NULL;
  bool is_tail = false;
  /*check whether the new_node is NULL*/
  if (!new_node) return NULL;
  /*check if list tail*/
  is_tail = !ptr->right && !ptr->down;
  /**
   *  ptr <-> next
   */
  next = ptr->right;
  /**
   * new_node <- next
   */
  if (next) next->left = new_node;
  /**
   * new_node <-> next
   */
  new_node->right = next;
  /**
   *  ptr -> new_node
   */
  ptr->right = new_node;
  /**
   *  ptr <-> new_node
   */
  new_node->left = ptr;
  /*if insert after the tail, set the tail*/
  if (is_tail) list->tail = new_node;
  return new_node;
}

doubll2d_elem *doubll2d_insert_col(doubll2d *list, doubll2d_elem *cursor, void **data,
                          size_t *size, size_t length) {
  /*insert a new col*/
  doubll2d_elem *up_most_ptr = NULL, *prev = NULL, *cur = NULL;
  int now_row = 0;
  /*check if the list is NULL*/
  if (!is_list_valid(list)) return NULL;
  /*check if length is less than dim_col*/
  if (length < doubll2d_dim_row(list)) return NULL;
  /*empty list*/
  if (!list->head) {
    if (data && size && length) {
      /*just create a new node*/
      list->head = list->tail = new_list_node(data[0], size[0]);
      list->dim_col = list->dim_row = 1;
      return list->head;
    }
    /*invalid case*/
    return NULL;
  }
#ifdef CHECK_LIST
  /*do list checking*/
  if (!check_list(list, cursor)) return NULL;
#endif
  if (!cursor || !data || !size) return NULL;
  /*get the left most ptr in this row*/
  up_most_ptr = cursor;
  /*loop to the left most*/
  while (up_most_ptr->up) up_most_ptr = up_most_ptr->up;
  /*from up -> down to insert right each node*/
  for (; up_most_ptr; up_most_ptr = up_most_ptr->down, ++now_row) {
    /*insert one node right*/
    if (!(cur = insert_right_one(list, up_most_ptr, data[now_row], size[now_row])))
      return NULL;
    /**
     * prev
     *  ^
     *  |
     * cur
     */
    cur->up = prev;
    /**
     * prev
     *  ^
     *  |
     *  v
     * cur
     */
    if (prev) prev->down = cur;
    /**
     * prev (x) ----- prev (cur)
     */
    prev = cur;
  }
  /*there's new col inserted*/
  ++list->dim_col;
  /*need to return the newly created element after the cursor*/
  return cursor->right;
}

/*delete a row*/
doubll2d_elem *doubll2d_delete_row(doubll2d *list, doubll2d_elem *cursor) {
  doubll2d_elem *left_most_ptr = cursor, *right_most_ptr = cursor, *ret = NULL, *next = NULL;
  /*check if the list is NULL*/
  if (!is_list_valid(list) || !cursor) return NULL;
#ifdef CHECK_LIST
  /*do list checking*/
  if (!check_list(list, cursor)) return NULL;
#endif
  /*loop left to get the left most ptr*/
  while (left_most_ptr->left) left_most_ptr = left_most_ptr->left;
  /*loop right to get the right most ptr*/
  while (right_most_ptr->right) right_most_ptr = right_most_ptr->right;
  /*the ret should be up, but if no above nodes need to return down*/
  ret = left_most_ptr == list->head ? cursor->down : cursor->up;
  /*if the tail is deleted, set tail up*/
  if (right_most_ptr == list->tail) list->tail = right_most_ptr->up;
  /*if the head is deleted, set head down*/
  if (left_most_ptr == list->head) list->head = left_most_ptr->down;
  /*left->right to delete the row*/
  for (; left_most_ptr; left_most_ptr = next) {
    /*up -> cur (x) ------- up -> down*/
    if (left_most_ptr->up) left_most_ptr->up->down = left_most_ptr->down;
    /*down -> cur(x) ------- down -> up*/
    if (left_most_ptr->down) left_most_ptr->down->up = left_most_ptr->up;
    /*since the current node will be freed, we need a next node*/
    next = left_most_ptr->right;
    /*free the current node's data*/
    free(left_most_ptr->data);
    /*free the current node*/
    free(left_most_ptr);
  }
  /*a row is deleted*/
  --list->dim_row;
  return ret;
}

/*delete a col*/
doubll2d_elem *doubll2d_delete_col(doubll2d *list, doubll2d_elem *cursor) {
  doubll2d_elem *up_most_ptr = cursor, *down_most_ptr = cursor, *ret = NULL, *next = NULL;
  /*check if the list is NULL*/
  if (!is_list_valid(list) || !cursor) return NULL;
#ifdef CHECK_LIST
  /*do list checking*/
  if (!check_list(list, cursor)) return NULL;
#endif
  /*loop up to get the up most ptr*/
  while (up_most_ptr->up) up_most_ptr = up_most_ptr->up;
  /*loop down to get the down most ptr*/
  while (down_most_ptr->down) down_most_ptr = down_most_ptr->down;
  /*the ret should be left, but if no left nodes need to return right*/
  ret = up_most_ptr == list->head ? cursor->right : cursor->left;
  /*if the head is deleted, set head right*/
  if (up_most_ptr == list->head) list->head = up_most_ptr->right;
  /*if the tail is deleted, set tail left*/
  if (down_most_ptr == list->tail) list->tail = down_most_ptr->left;
  /*up->down to delete the col*/
  for (; up_most_ptr; up_most_ptr = next) {
    /*left -> cur (x) ------- left -> right*/
    if (up_most_ptr->left) up_most_ptr->left->right = up_most_ptr->right;
    /*cur(x) <- right ------- left <- right*/
    if (up_most_ptr->right) up_most_ptr->right->left = up_most_ptr->left;
    /*since the current node will be freed, we need a next node*/
    next = up_most_ptr->down;
    /*free the current node's data*/
    free(up_most_ptr->data);
    /*free the current node*/
    free(up_most_ptr);
  }
  /*a col is deleted*/
  --list->dim_col;
  return ret;
}

/*  Purge all items from the list. */
void doubll2d_purge(doubll2d *list) {
  doubll2d_elem *row_ptr = NULL, *col_ptr = NULL, *next_row = NULL, *next_col = NULL;
  /*check if list is NULL*/
  if (!is_list_valid(list)) return;
  row_ptr = col_ptr = list->head;
  /*loop through row*/
  for (; row_ptr; row_ptr = next_row) {
    next_row = row_ptr->down;
    /*loop through col*/
    for (col_ptr = row_ptr; col_ptr; col_ptr = next_col) {
      next_col = col_ptr->right;
      /*free each element*/
      free(col_ptr->data);
      free(col_ptr);
    }
  }
  /*reset the list*/
  list->head = list->tail = NULL;
  list->dim_col = list->dim_row = 0;
}

/*find the maximum element*/
doubll2d_elem *doubll2d_find_max(doubll2d *list, list_less_func *less) {
  doubll2d_elem *row_ptr = NULL, *col_ptr = NULL, *ret = NULL;
  if (!is_list_valid(list) || !list->head || !less) return NULL;
  /*init ret as the first element*/
  ret = row_ptr = col_ptr = list->head;
  /*loop through row*/
  for (; row_ptr; row_ptr = row_ptr->down) {
    /*loop through col*/
    for (col_ptr = row_ptr; col_ptr; col_ptr = col_ptr->right) {
      if (less(ret, col_ptr)) ret = col_ptr;
    }
  }
  return ret;
}

/*find the minimum element*/
doubll2d_elem *doubll2d_find_min(doubll2d *list, list_less_func *less) {
  doubll2d_elem *row_ptr = NULL, *col_ptr = NULL, *ret = NULL;
  if (!is_list_valid(list) || !list->head || !less) return NULL;
  /*init ret as the first element*/
  ret = row_ptr = col_ptr = list->head;
  /*loop through row*/
  for (; row_ptr; row_ptr = row_ptr->down) {
    /*loop through col*/
    for (col_ptr = row_ptr; col_ptr; col_ptr = col_ptr->right) {
      if (less(col_ptr, ret)) ret = col_ptr;
    }
  }
  return ret;
}
