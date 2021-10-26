#ifndef RBT_H
#define RBT_H
#include <stdarg.h>
#ifndef BST_H
#define RED_COLOR 1
#define BLACK_COLOR 0
#define RedBlackTree(KEY, VALUE, IS_LESS, IS_MORE) \
typedef struct KEY ## _ ## VALUE ## _rbt * KEY ## _ ## VALUE ## _rbt; \
typedef struct List_ ## KEY ## _ ## VALUE ## _pair *List_ ## KEY ## _ ## VALUE ## _pair; \
typedef struct KEY ## _ ## VALUE ## _pair * KEY ## _ ## VALUE ## _pair; \
struct KEY ## _ ## VALUE ## _pair { \
  /* basic pair structure to hold key and value and return from find() just like std::pair */ \
  KEY key; \
  VALUE value; \
}; \
struct List_ ## KEY ## _ ## VALUE ## _pair { \
  /* a list structure basically for inorder traversal, contains the key-value pair as entry and pointer to next */ \
  KEY ## _ ## VALUE ## _pair entry; \
  List_ ## KEY ## _ ## VALUE ## _pair next; \
}; \
\
List_ ## KEY ## _ ## VALUE ## _pair make_list_ ## KEY ## _ ## VALUE ## _(KEY key, VALUE value){ \
  List_ ## KEY ## _ ## VALUE ## _pair p_list = malloc(sizeof(struct List_ ## KEY ## _ ## VALUE ## _pair)); \
  KEY ## _ ## VALUE ## _pair p_entry = malloc(sizeof(struct KEY ## _ ## VALUE ## _pair)); \
  p_entry->key = key; \
  p_entry->value = value; \
  p_list->entry = p_entry; \
  p_list->next = NULL; \
  return p_list; \
} \
\
List_ ## KEY ## _ ## VALUE ## _pair last_ ## KEY ## _ ## VALUE ## _(List_ ## KEY ## _ ## VALUE ## _pair lst) { \
  /* finds the last element of a list */ \
  if (!lst) return NULL; /* only matters the first time */ \
  if (lst->next == NULL) return lst; \
  /* otherwise recurse */ \
  return last_ ## KEY ## _ ## VALUE ## _(lst->next); \
} \
List_ ## KEY ## _ ## VALUE ## _pair append_List_ ## KEY ## _ ## VALUE ## _(int numLists, ...) { \
  /* useful for appending sublists in inorder method, uses varargs */ \
  va_list valst; \
  va_start(valst, numLists);\
  List_ ## KEY ## _ ## VALUE ## _pair temp_list, full_list; \
  temp_list = va_arg(valst, List_ ## KEY ## _ ## VALUE ## _pair); \
  int count = 1; \
  while (!temp_list && count <= numLists) { \
    /* remove all NULL lists (like '() in scheme is discarded in (append ..)) */ \
    temp_list = va_arg(valst, List_ ## KEY ## _ ## VALUE ## _pair); \
    count++; \
  } \
  full_list = temp_list; /* saving a reference to the first list, all other lists will be concatenated at their ends */ \
  temp_list = last_ ## KEY ## _ ## VALUE ## _(temp_list); \
  for (int i = count; i < numLists; i++) { \
    temp_list->next = va_arg(valst, List_ ## KEY ## _ ## VALUE ## _pair); \
    temp_list = last_ ## KEY ## _ ## VALUE ## _(temp_list); \
  } \
  return full_list;\
} \
struct KEY ## _ ## VALUE ## _rbt { \
  KEY ## _ ## VALUE ## _pair value_type; \
  KEY ## _ ## VALUE ## _rbt left; \
  KEY ## _ ## VALUE ## _rbt right; \
  int size; \
  int color; /* 1 for Red, 0 for Black */ \
}; \
KEY ## _ ## VALUE ## _rbt make_ ## KEY ## _ ## VALUE ## _rbt(KEY key, VALUE value, int size, int color) { \
  KEY ## _ ## VALUE ## _rbt p_rbt = malloc(sizeof(struct KEY ## _ ## VALUE ## _rbt)); \
  KEY ## _ ## VALUE ## _pair p_pair = malloc(sizeof(struct KEY ## _ ## VALUE ## _pair)); \
  p_pair->key = key; \
  p_pair->value = value; \
  p_rbt->value_type = p_pair; \
  p_rbt->left = NULL; \
  p_rbt->right = NULL; \
  p_rbt->size = size; \
  p_rbt->color = color; \
  return p_rbt; \
} \
void free_ ## KEY ## _ ## VALUE ## _rbt(KEY ## _ ## VALUE ## _rbt x) { \
  free(x); \
} \
int size_ ## KEY ## _ ## VALUE ## _rbt(KEY ## _ ## VALUE ## _rbt x) { \
  if (!x) return 0; \
  return x->size; \
} \
int isRed_ ## KEY ## _ ## VALUE ## _rbt(KEY ## _ ## VALUE ## _rbt x) { \
  if (!x) return 0; \
  return x->color == RED_COLOR; \
} \
KEY ## _ ## VALUE ## _rbt rotate_left(KEY ## _ ## VALUE ## _rbt h) { \
  KEY ## _ ## VALUE ## _rbt x = h->right; \
  h->right = x->left; \
  x->left = h; \
  x->color = h->color; \
  h->color = RED_COLOR; \
  x->size = h->size; \
  h->size = 1 + size_ ## KEY ## _ ## VALUE ## _rbt(h->left) + size_ ## KEY ## _ ## VALUE ## _rbt(h->right); \
  return x; \
  } \
KEY ## _ ## VALUE ## _rbt rotate_right(KEY ## _ ## VALUE ## _rbt h) { \
  KEY ## _ ## VALUE ## _rbt x = h->left; \
  h->left = x->right; \
  x->right = h; \
  x->color = h->color; \
  h->color = RED_COLOR; \
  x->size = h->size; \
  h->size = 1 + size_ ## KEY ## _ ## VALUE ## _rbt(h->left) + size_ ## KEY ## _ ## VALUE ## _rbt(h->right); \
  return x; \
} \
void flip_colors(KEY ## _ ## VALUE ## _rbt h) { \
  h->color = RED_COLOR; \
  h->left->color = BLACK_COLOR; \
  h->right->color = BLACK_COLOR; \
} \
KEY ## _ ## VALUE ## _rbt insert_helper_ ## KEY ## _ ## VALUE ## _rbt(KEY ## _ ## VALUE ## _rbt root, KEY key, VALUE value) { \
  if (!root) return make_ ## KEY ## _ ## VALUE ## _rbt(key, value, 1, RED_COLOR); \
  if (IS_LESS ## _(key, root->value_type->key)) root->left = insert_helper_ ## KEY ## _ ## VALUE ## _rbt(root->left, key, value); \
  else if (IS_MORE ## _(key, root->value_type->key)) root->right = insert_helper_ ## KEY ## _ ## VALUE ## _rbt(root->right, key, value); \
  else root->value_type->value = value; \
  if (isRed_ ## KEY ## _ ## VALUE ## _rbt(root->right) && !isRed_ ## KEY ## _ ## VALUE ## _rbt(root->left)) root = rotate_left(root); \
  if (isRed_ ## KEY ## _ ## VALUE ## _rbt(root->left) && isRed_ ## KEY ## _ ## VALUE ## _rbt(root->left->left)) root = rotate_right(root); \
  if (isRed_ ## KEY ## _ ## VALUE ## _rbt(root->left) && isRed_ ## KEY ## _ ## VALUE ## _rbt(root->right)) flip_colors(root); \
  root->size = 1 + size_ ## KEY ## _ ## VALUE ## _rbt(root->left) + size_ ## KEY ## _ ## VALUE ## _rbt(root->right); \
  return root; \
} \
KEY ## _ ## VALUE ## _rbt insert_ ## KEY ## _ ## VALUE ## _rbt(KEY ## _ ## VALUE ## _rbt root, KEY key, VALUE value) { \
  root = insert_helper_ ## KEY ## _ ## VALUE ## _rbt(root, key, value); \
  root->color = BLACK_COLOR; \
  return root; \
}
#else
#define RedBlackTree(KEY, VALUE, IS_LESS, IS_MORE) int add(int a , int b) {return 0;}
#endif
#endif
