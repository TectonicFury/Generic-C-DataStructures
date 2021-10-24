// todo: add iterative inorder traversal, deletion
#ifndef BST_H
#define BST_H
#include <stdarg.h>
#define BST(KEY, VALUE, IS_LESS, IS_MORE) \
typedef struct KEY ## _ ## VALUE ## _bst * KEY ## _ ## VALUE ## _bst; \
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
struct KEY ## _ ## VALUE ## _bst{ \
  /* the basic node structure of the BST */ \
  KEY ## _ ## VALUE ## _pair value_type; \
  KEY ## _ ## VALUE ## _bst left; \
  KEY ## _ ## VALUE ## _bst right; \
  int size; \
}; \
\
KEY ## _ ## VALUE ## _bst make ## _ ## KEY ## _ ## VALUE ## _bst(KEY key, VALUE value, int size) {\
  /* make a bst node */ \
  KEY ## _ ## VALUE ## _bst p_bst = malloc(sizeof(struct KEY ## _ ## VALUE ## _bst)); \
  KEY ## _ ## VALUE ## _pair p_pair = malloc(sizeof(struct KEY ## _ ## VALUE ## _pair)); \
  p_pair->key = key; \
  p_pair->value = value; \
  p_bst->value_type = p_pair; \
  p_bst->left  = NULL; \
  p_bst->right = NULL; \
  p_bst->size = size; \
  return p_bst; \
} \
void free_ ## KEY ## _ ## VALUE ## _bst(KEY ## _ ## VALUE ## _bst x) { \
  /* if the key and value are malloc'ed, we have to free them first before calling this function */ \
  free(x); \
} \
int size_ ## KEY ## _ ## VALUE ## _bst(KEY ## _ ## VALUE ## _bst x) { \
  /* size of node */ \
  if (!x) return 0; \
  return x->size; \
} \
KEY ## _ ## VALUE ## _bst insert_ ## KEY ## _ ## VALUE ## _bst(KEY ## _ ## VALUE ## _bst root, KEY key, VALUE value) { \
  if (!root) return make ## _ ## KEY ## _ ## VALUE ## _bst(key, value, 1); \
  if (IS_LESS ## _(key, root->value_type->key)) {root->left = \
      insert_ ## KEY ## _ ## VALUE ## _bst(root->left, key, value); \
  }\
  else if (IS_MORE ## _(key, root->value_type->key)) {root->right = \
      insert_ ## KEY ## _ ## VALUE ## _bst(root->right, key, value); \
  } \
  else root->value_type->value = value; \
  root->size = size_ ## KEY ## _ ## VALUE ## _bst(root->left) + \
               size_ ## KEY ## _ ## VALUE ## _bst(root->right) + 1; \
  return root; \
} \
KEY ## _ ## VALUE ## _pair find_in_ ## KEY ## _ ## VALUE ## _bst(KEY ## _ ## VALUE ## _bst root, KEY key) { \
 if (!root) return NULL; \
 if (IS_LESS ## _(key, root->value_type->key)) return find_in_ ## KEY ## _ ## VALUE ## _bst(root->left, key); \
 else if (IS_MORE ## _(key, root->value_type->key)) return find_in_ ## KEY ## _ ## VALUE ## _bst(root->right, key); \
 else return root->value_type; \
} \
List_ ## KEY ## _ ## VALUE ## _pair recursive_inorder_ ## KEY ## _ ## VALUE ## _bst(KEY ## _ ## VALUE ## _bst root) { \
  /* returns a list of entries inorder */ \
  /* causes stack overflow for large bsts due to recursive nature */ \
  if (!root) return NULL; \
  return append_List_ ## KEY ## _ ## VALUE ## _(3, recursive_inorder_ ## KEY ## _ ## VALUE ## _bst(root->left), \
  make_list_ ## KEY ## _ ## VALUE ## _(root->value_type->key, root->value_type->value), \
  recursive_inorder_ ## KEY ## _ ## VALUE ## _bst(root->right));\
} \
KEY ## _ ## VALUE ## _pair min_ ## KEY ## _ ## VALUE ## _bst(KEY ## _ ## VALUE ## _bst root) { \
  /* return minimum key-value pair */ \
  if (!root) return NULL; \
  if (!(root->left)) return root->value_type; \
  return min_ ## KEY ## _ ## VALUE ## _bst(root->left); \
} \
KEY ## _ ## VALUE ## _pair max_ ## KEY ## _ ## VALUE ## _bst(KEY ## _ ## VALUE ## _bst root) { \
  /* return maximum key-value pair */ \
  if (!root) return NULL; \
  if (!(root->right)) return root->value_type; \
  return max_ ## KEY ## _ ## VALUE ## _bst(root->right); \
} \
KEY ## _ ## VALUE ## _pair helper_floor_ ## KEY ## _ ## VALUE ## _bst(KEY ## _ ## VALUE ## _bst root, KEY key, KEY ## _ ## VALUE ## _bst floor_ptr) { \
  if (!root) { \
    if (floor_ptr) { \
      return floor_ptr->value_type; \
    } else { \
      return NULL; \
    }} \
  if (IS_MORE ## _(key, root->value_type->key)) return helper_floor_ ## KEY ## _ ## VALUE ## _bst(root->right, key, root); \
  if (IS_LESS ## _(key, root->value_type->key)) return helper_floor_ ## KEY ## _ ## VALUE ## _bst(root->left, key, floor_ptr); \
  return root->value_type; \
} \
KEY ## _ ## VALUE ## _pair floor_ ## KEY ## _ ## VALUE ## _bst(KEY ## _ ## VALUE ## _bst root, KEY key) { \
  return helper_floor_ ## KEY ## _ ## VALUE ## _bst(root, key, NULL); \
} \
KEY ## _ ## VALUE ## _pair helper_ceiling_ ## KEY ## _ ## VALUE ## _bst(KEY ## _ ## VALUE ## _bst root, KEY key, KEY ## _ ## VALUE ## _bst ceiling_ptr) { \
  if (!root) { \
    if (ceiling_ptr) { \
      return ceiling_ptr->value_type; \
    } else { \
      return NULL; \
    } \
  } \
  if (IS_LESS ## _(key, root->value_type->key)) return helper_ceiling_ ## KEY ## _ ## VALUE ## _bst(root->left, key, root); \
  if (IS_MORE ## _(key, root->value_type->key)) return helper_ceiling_ ## KEY ## _ ## VALUE ## _bst(root->right, key, ceiling_ptr); \
  return root->value_type; \
} \
KEY ## _ ## VALUE ## _pair ceiling_ ## KEY ## _ ## VALUE ## _bst(KEY ## _ ## VALUE ## _bst root, KEY key) { \
  return helper_ceiling_ ## KEY ## _ ## VALUE ## _bst(root, key, NULL); \
} \
KEY ## _ ## VALUE ## _pair select_rank_ ## KEY ## _ ## VALUE ## _bst(KEY ## _ ## VALUE ## _bst root, int rank) { \
  if (!root) return NULL; \
  int t = size_ ## KEY ## _ ## VALUE ## _bst(root->left); \
  if (rank < t) return select_rank_ ## KEY ## _ ## VALUE ## _bst(root->left, rank); \
  if (rank == t) return root->value_type; \
  return select_rank_ ## KEY ## _ ## VALUE ## _bst(root->right, rank - t - 1); \
} \
int rank_ ## KEY ## _ ## VALUE ## _bst(KEY ## _ ## VALUE ## _bst root, KEY key) { \
  if (!root) return 0; \
  if (IS_LESS ## _(key, root->value_type->key)) return rank_ ## KEY ## _ ## VALUE ## _bst(root->left, key); \
  if (IS_MORE ## _(key, root->value_type->key)) return 1 + size_ ## KEY ## _ ## VALUE ## _bst(root->left) + rank_ ## KEY ## _ ## VALUE ## _bst(root->right, key); \
  return size_ ## KEY ## _ ## VALUE ## _bst(root->left); \
} \
KEY ## _ ## VALUE ## _bst deleteMin_ ## KEY ## _ ## VALUE ## _bst(KEY ## _ ## VALUE ## _bst root, void (* destruct) (KEY ## _ ## VALUE ## _pair)) { \
  /* to properly clean up, we have to pass a function pointer to a custom 'clean-up' function for the specific data in value_type */ \
  if (!root) return NULL; \
  if (!root->left) { \
    destruct(root->value_type); \
    KEY ## _ ## VALUE ## _bst right_child = root->right; \
    free(root); \
    return right_child; \
  }  \
  root->left = deleteMin_ ## KEY ## _ ## VALUE ## _bst(root->left, destruct); \
  root->size = size_ ## KEY ## _ ## VALUE ## _bst(root->left) + size_ ## KEY ## _ ## VALUE ## _bst(root->right) + 1; \
  return root; \
} \
KEY ## _ ## VALUE ## _bst deleteMax_ ## KEY ## _ ## VALUE ## _bst(KEY ## _ ## VALUE ## _bst root, void (* destruct) (KEY ## _ ## VALUE ## _pair)) { \
  if (!root) return NULL; \
  if (!root->right) { \
    destruct(root->value_type); \
    KEY ## _ ## VALUE ## _bst left_child = root->left; \
    free(root); \
    return left_child;\
  } \
  root->right = deleteMax_ ## KEY ## _ ## VALUE ## _bst(root->right, destruct); \
  root->size = size_ ## KEY ## _ ## VALUE ## _bst(root->left) + size_ ## KEY ## _ ## VALUE ## _bst(root->right) + 1; \
  return root; \
  }
#endif
