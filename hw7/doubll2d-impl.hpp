namespace __detail {
  // list_row_elem_iter
  // left to right in the same row
  template <typename T>
  typename list_row_elem_iter<T>::reference list_row_elem_iter<T>::operator*() {
    // return the data
    if (inner) return inner->data;
    // !Error!!!!
    for (;;);
    return inner->data;
  }

  template <typename T>
  typename list_row_elem_iter<T>::pointer list_row_elem_iter<T>::operator->() {
    // return the addr of data
    if (inner) return &inner->data;
    // !Error!!!!
    for (;;);
    return &inner->data;
  }

  // ++p
  template <typename T>
  list_row_elem_iter<T> &list_row_elem_iter<T>::operator++() {
    // move next (right)
    if (inner) inner = inner->right;
    return *this;
  }

  // p++
  template <typename T>
  list_row_elem_iter<T> list_row_elem_iter<T>::operator++(int) {
    // store this
    list_row_elem_iter<T> ret(inner);
    operator++();
    return ret;
  }

  // --p
  template <typename T>
  list_row_elem_iter<T> &list_row_elem_iter<T>::operator--() {
    // move prev (left)
    if (inner) inner = inner->left;
    return *this;
  }

  // p--
  template <typename T>
  list_row_elem_iter<T> list_row_elem_iter<T>::operator--(int) {
    // store this
    list_row_elem_iter<T> ret(inner);
    operator--();
    return ret;
  }

  // op: ==
  template <typename T>
  bool list_row_elem_iter<T>::operator==(const list_row_elem_iter<T> &other) {
    // check the inner pointer
    return inner == other.inner;
  }

  // op: !=
  template <typename T>
  bool list_row_elem_iter<T>::operator!=(const list_row_elem_iter<T> &other) {
    return !(*this == other);
  }

  // list_col_elem_iter
  // top to bottom in the same col
  template <typename T>
  typename list_col_elem_iter<T>::reference list_col_elem_iter<T>::operator*() {
    // return the data
    if (inner) return inner->data;
    // !Error!!!!
    for (;;);
    return inner->data;
  }

  template <typename T>
  typename list_col_elem_iter<T>::pointer list_col_elem_iter<T>::operator->() {
    // return the addr of data
    if (inner) return &inner->data;
    // !Error!!!!
    for (;;);
    return &inner->data;
  }

  // ++p
  template <typename T>
  list_col_elem_iter<T> &list_col_elem_iter<T>::operator++() {
    // move to next (down)
    if (inner) inner = inner->down;
    return *this;
  }

  // p++
  template <typename T>
  list_col_elem_iter<T> list_col_elem_iter<T>::operator++(int) {
    // store this
    list_col_elem_iter<T> ret(inner);
    operator++();
    return ret;
  }

  // --p
  template <typename T>
  list_col_elem_iter<T> &list_col_elem_iter<T>::operator--() {
    // move to prev (up)
    if (inner) inner = inner->up;
    return *this;
  }

  // p--
  template <typename T>
  list_col_elem_iter<T> list_col_elem_iter<T>::operator--(int) {
    // store this
    list_col_elem_iter<T> ret(inner);
    operator--();
    return ret;
  }

  // op: ==
  template <typename T>
  bool list_col_elem_iter<T>::operator==(const list_col_elem_iter<T> &other) {
    // check the inner pointer
    return inner == other.inner;
  }

  // op: !=
  template <typename T>
  bool list_col_elem_iter<T>::operator!=(const list_col_elem_iter<T> &other) {
    return !(*this == other);
  }

  // list_row_iter
  // top to bottom through the list
  template <typename T>
  typename list_row_iter<T>::iterator list_row_iter<T>::begin() {
    // begin: left most
    return iterator(left);
  }

  template <typename T>
  typename list_row_iter<T>::iterator list_row_iter<T>::end() {
    // end: the next of rightmost
    return ++iterator(right);
  }

  template <typename T>
  typename list_row_iter<T>::reverse_iterator list_row_iter<T>::rbegin() {
    // rbegin: right most
    return reverse_iterator(iterator(right));
  }

  template <typename T>
  typename list_row_iter<T>::reverse_iterator list_row_iter<T>::rend() {
    // rend: next(reversed) of leftmost
    return ++reverse_iterator(iterator(left));
  }

  template <typename T>
  typename list_row_iter<T>::reference list_row_iter<T>::operator*() {
    return *this;
  }

  template <typename T>
  typename list_row_iter<T>::pointer list_row_iter<T>::operator->() {
    return this;
  }

  // ++p
  template <typename T>
  list_row_iter<T> &list_row_iter<T>::operator++() {
    // move to next (down)
    if (left) left = left->down;
    if (right) right = right->down;
    return *this;
  }

  // p++
  template <typename T>
  list_row_iter<T> list_row_iter<T>::operator++(int) {
    // store this
    list_row_iter<T> ret(left, right);
    operator++();
    return ret;
  }

  // --p
  template <typename T>
  list_row_iter<T> &list_row_iter<T>::operator--() {
    // move to prev (up)
    if (left) left = left->up;
    if (right) right = right->up;
    return *this;
  }

  // p--
  template <typename T>
  list_row_iter<T> list_row_iter<T>::operator--(int) {
    // store this
    list_row_iter<T> ret(left, right);
    operator--();
    return ret;
  }

  // op: ==
  template <typename T>
  bool list_row_iter<T>::operator==(const list_row_iter<T> &other) {
    // check the both inner pointers
    return left == other.left && right == other.right;
  }

  // op: !=
  template <typename T>
  bool list_row_iter<T>::operator!=(const list_row_iter<T> &other) {
    return !(*this == other);
  }

  // list_col_iter
  // move from left to right
  template <typename T>
  typename list_col_iter<T>::iterator list_col_iter<T>::begin() {
    // begin: upmost
    return iterator(up);
  }

  template <typename T>
  typename list_col_iter<T>::iterator list_col_iter<T>::end() {
    // end: the next of downmost
    return ++iterator(down);
  }

  template <typename T>
  typename list_col_iter<T>::reverse_iterator list_col_iter<T>::rbegin() {
    // rbegin: downmost
    return reverse_iterator(iterator(down));
  }

  template <typename T>
  typename list_col_iter<T>::reverse_iterator list_col_iter<T>::rend() {
    // rend: the next (reversed) of upmost
    return ++reverse_iterator(iterator(up));
  }

  template <typename T>
  typename list_col_iter<T>::reference list_col_iter<T>::operator*() {
    return *this;
  }

  template <typename T>
  typename list_col_iter<T>::pointer list_col_iter<T>::operator->() {
    return this;
  }

  // ++p
  template <typename T>
  list_col_iter<T> &list_col_iter<T>::operator++() {
    // move to next (right)
    if (up) up = up->right;
    if (down) down = down->right;
    return *this;
  }

  // p++
  template <typename T>
  list_col_iter<T> list_col_iter<T>::operator++(int) {
    // store this
    list_col_iter<T> ret(up, down);
    operator++();
    return ret;
  }

  // --p
  template <typename T>
  list_col_iter<T> &list_col_iter<T>::operator--() {
    // move to prev (left)
    if (up) up = up->left;
    if (down) down = down->left;
    return *this;
  }

  // p--
  template <typename T>
  list_col_iter<T> list_col_iter<T>::operator--(int) {
    // store this
    list_col_iter<T> ret(up, down);
    operator--();
    return ret;
  }

  // op: ==
  template <typename T>
  bool list_col_iter<T>::operator==(const list_col_iter<T> &other) {
    // check both inner pointers
    return up == other.up && down == other.down;
  }

  // op: !=
  template <typename T>
  bool list_col_iter<T>::operator!=(const list_col_iter<T> &other) {
    return !(*this == other);
  }
}  // namespace __detail

// doubll2d
template <typename T>
typename doubll2d<T>::row_iter doubll2d<T>::row_begin() {
  // row_begin: (up left, up right)
  return row_iter(up_left, up_right);
}

template <typename T>
typename doubll2d<T>::row_iter doubll2d<T>::row_end() {
  // row_end: next of (down left, down right)
  return ++row_iter(down_left, down_right);
}

template <typename T>
typename doubll2d<T>::row_riter doubll2d<T>::row_rbegin() {
  // row_rbegin: (down left, down right)
  return row_riter(row_iter(down_left, down_right));
}

template <typename T>
typename doubll2d<T>::row_riter doubll2d<T>::row_rend() {
  // row_rend: next (reversed) of (up left, up right)
  return ++row_riter(row_iter(up_left, up_right));
}

template <typename T>
typename doubll2d<T>::col_iter doubll2d<T>::col_begin() {
  // col_begin: (left up, left down)
  return col_iter(up_left, down_left);
}

template <typename T>
typename doubll2d<T>::col_iter doubll2d<T>::col_end() {
  // col_end: the next of (right up, right down)
  return ++col_iter(up_right, down_right);
}

template <typename T>
typename doubll2d<T>::col_riter doubll2d<T>::col_rbegin() {
  // col_rbegin: (right up, right down)
  return col_riter(col_iter(up_right, down_right));
}

template <typename T>
typename doubll2d<T>::col_riter doubll2d<T>::col_rend() {
  // col_rend: the next (reversed) of (left up, left down)
  return ++col_riter(col_iter(up_left, down_left));
}

// helpers
// get the length of a list
template <typename InputIter>
int getListLength(InputIter begin, InputIter end) {
  // move through the list
  InputIter it = begin;
  int ret = 0;
  // sum up the length
  while (it != end) ++ret, ++it;
  return ret;
}

template <typename T, typename InputIter>
void fillNodeBuffer(__detail::list_node<T> **buf, InputIter begin, InputIter end,
                    int len) {
  int i = 0;
  InputIter it = begin;
  for (; i < len && it != end; ++i)
    buf[i] = new __detail::list_node<T>(*it++);
  for (; i < len; ++i) {
    buf[i] = new __detail::list_node<T>(T());
  }
}

// insert row
template <typename T>
template <typename input_iter>
typename doubll2d<T>::row_iter doubll2d<T>::insert_row(
    doubll2d<T>::row_iter cursor, input_iter begin, input_iter end) {
  using Node = __detail::list_node<T>;
  Node **buf;
  if (get_dim_col() == 0 || get_dim_row() == 0) { // list empty
    int len = getListLength(begin, end);
    if (len == 0) return row_end(); // input is empty
    buf = new Node*[len];
    // insert all from begin to end
    fillNodeBuffer(buf, begin, end, len);
    // connect
    for (int i = 0; i < len; ++i) {
      if (i > 0) buf[i]->left = buf[i - 1];
      if (i + 1 < len) buf[i]->right = buf[i + 1];
    }
    // ret
    row_iter ret(buf[0], buf[len - 1]);
    // the only row
    up_left = down_left = buf[0];
    up_right = down_right = buf[len - 1];
    dim_col = len;
    dim_row = 1;
    delete[] buf; // delete buf
    return ret;
  }
  // insert length
  int len = dim_col;
  buf = new Node*[len];
  fillNodeBuffer(buf, begin, end, len);
  // connect bufs
  for (int i = 0; i < len; ++i) {
    if (i > 0) buf[i]->left = buf[i - 1];
    if (i + 1 < len) buf[i]->right = buf[i + 1];
  }
  if (cursor == row_end()) {
    // insert above the first row
    Node *cur = up_left;
    for (int i = 0; i < len; ++i) {
      // connect buf & first row
      cur->up = buf[i];
      buf[i]->down = cur;
      cur = cur->right;
    }
    // update up pointers
    up_left = buf[0];
    up_right = buf[len - 1];
  } else {
    // normal
    Node *prev = cursor.begin().inner;
    Node *next = prev->down;
    for (int i = 0; i < len; ++i) {
      buf[i]->up = prev;
      prev->down = buf[i];
      prev = prev->right;
    }
    if (next) {
      for (int i = 0; i < len; ++i) {
        buf[i]->down = next;
        next->up = buf[i];
        next = next->right;
      }
    } else {
      // insert after last row
      // update down pointers
      down_left = buf[0];
      down_right = buf[len - 1];
    }
  }
  ++dim_row;
  row_iter ret(buf[0], buf[len - 1]);
  delete[] buf;
  return ret;
}

// insert col
template <typename T>
template <typename input_iter>
typename doubll2d<T>::col_iter doubll2d<T>::insert_col(
    doubll2d<T>::col_iter cursor, input_iter begin, input_iter end) {
   using Node = __detail::list_node<T>;
  Node **buf;
  if (get_dim_col() == 0 || get_dim_row() == 0) { // list empty
    int len = getListLength(begin, end);
    if (len == 0) return col_end(); // input is empty
    buf = new Node*[len];
    // insert all from begin to end
    fillNodeBuffer(buf, begin, end, len);
    // connect
    for (int i = 0; i < len; ++i) {
      if (i > 0) buf[i]->up = buf[i - 1];
      if (i + 1 < len) buf[i]->down = buf[i + 1];
    }
    // ret
    col_iter ret(buf[0], buf[len - 1]);
    // the only col
    up_left = up_right = buf[0];
    down_left = down_right = buf[len - 1];
    dim_col = 1;
    dim_row = len;
    delete[] buf; // delete buf
    return ret;
  }
  // insert length
  int len = dim_row;
  buf = new Node*[len];
  fillNodeBuffer(buf, begin, end, len);
  // connect bufs
  for (int i = 0; i < len; ++i) {
    if (i > 0) buf[i]->up = buf[i - 1];
    if (i + 1 < len) buf[i]->down = buf[i + 1];
  }
  if (cursor == col_end()) {
    // insert before the first col
    Node *cur = up_left;
    for (int i = 0; i < len; ++i) {
      // connect buf & first col
      cur->left = buf[i];
      buf[i]->right = cur;
      cur = cur->down;
    }
    // update left pointers
    up_left = buf[0];
    down_left = buf[len - 1];
  } else {
    // normal
    Node *prev = cursor.begin().inner;
    Node *next = prev->right;
    for (int i = 0; i < len; ++i) {
      buf[i]->left = prev;
      prev->right = buf[i];
      prev = prev->down;
    }
    if (next) {
      for (int i = 0; i < len; ++i) {
        buf[i]->right = next;
        next->left = buf[i];
        next = next->down;
      }
    } else {
      // insert after last col
      // update right pointers
      up_right = buf[0];
      down_right = buf[len - 1];
    }
  }
  ++dim_col;
  col_iter ret(buf[0], buf[len - 1]);
  delete[] buf;
  return ret;
}


// delete row
template <typename T>
typename doubll2d<T>::row_iter doubll2d<T>::delete_row(
    doubll2d<T>::row_iter cursor) {
  using Node = __detail::list_node<T>;  // list node
  if (cursor == row_end() || get_dim_row() == 0) return row_end(); // row_end case / empty list
  Node *cur = cursor.begin().inner, *next = nullptr;
  bool isFirstRow = !cur->up;
  bool isLastRow = !cur->down;
  auto ret = cursor;
  if (isFirstRow) {
    // update up pointers
    up_left = up_left->down;
    up_right = up_right->down; 
    ++ret;
  } else {
    // above the cursor
    --ret;
  }
  if (isLastRow) {
    // update down pointers
    down_left = down_left->up;
    down_right = down_right->up;
  }
  for (; cur; cur = next) {
    next = cur->right;
    // update connections
    if (cur->up) cur->up->down = cur->down;
    if (cur->down) cur->down->up = cur->up;
    delete cur;
  }
  if (--dim_row == 0) {
    clear();
    return row_end();
  }
  return ret;
}

// delete col
template <typename T>
typename doubll2d<T>::col_iter doubll2d<T>::delete_col(
    doubll2d<T>::col_iter cursor) {
  using Node = __detail::list_node<T>;  // list node
  if (cursor == col_end() || get_dim_col() == 0) return col_end(); // col_end case / empty list
  Node *cur = cursor.begin().inner, *next = nullptr;
  bool isFirstCol = !cur->left;
  bool isLastCol = !cur->right;
  auto ret = cursor;
  if (isFirstCol) {
    // update left pointers
    up_left = up_left->right;
    down_left = down_left->right; 
    ++ret;
  } else {
    // left to the cursor
    --ret;
  }
  if (isLastCol) {
    // update right pointers
    up_right = up_right->left;
    down_right = down_right->left;
  }
  for (; cur; cur = next) {
    next = cur->down;
    // update connections
    if (cur->left) cur->left->right = cur->right;
    if (cur->right) cur->right->left = cur->left;
    delete cur;
  }
  if (--dim_col == 0) {
    clear();
    return col_end();
  }
  return ret;
}

template <typename T>
void doubll2d<T>::clear() {
  if (get_dim_col() == 0 || get_dim_row() == 0) {
    // clear all
    dim_col = dim_row = 0;
    up_left = up_right = down_left = down_right = nullptr;
    return;
  }
  using Node = __detail::list_node<T>;  // list node
  Node **buf = new Node*[get_dim_col() * get_dim_row()];
  int cnt = 0;
  // collect all nodes
  for (Node *row = up_left; row; row = row->down) {
    for (Node *p = row; p; p = p->right) {
      buf[cnt++] = p;
    }
  }
  for (int i = 0; i < cnt; ++i) delete buf[i];
  delete[] buf;
  // clear all
  dim_col = dim_row = 0;
  up_left = up_right = down_left = down_right = nullptr;
}

template <typename T>
template <typename R>
R doubll2d<T>::reduce(std::function<R(R, const T &)> fn, R init) {
  using Node = __detail::list_node<T>;  // list node
  typename std::remove_reference<R>::type ret = init;
  // loop through row
  for (Node *row = up_left; row; row = row->down) {
    // loop through col
    for (Node *p = row; p; p = p->right) {
      ret = fn(ret, p->data);
    }
  }
  return ret;
}