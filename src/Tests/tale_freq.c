// this file tests RedBlackTree on a 'real' application: counts word frequency for A Tale of Two Cities
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <assert.h>
#include <time.h>
#include "../includes/rbt.h"
typedef char *my_string;
int less_string_(char *s1, char *s2) {
  if (strcmp(s1, s2) < 0) return 1;
  return 0;
}
int more_string_(char *s1, char *s2) {
  if (strcmp(s1, s2) > 0) return 1;
  return 0;
}

RedBlackTree(my_string, int, less_string, more_string)

void destruct_my_string_int_pair(my_string_int_pair pair) {
  // basic freeing, no recursive freeing for primitive data members (here ints)
  if (pair) {
    if (pair->key) {
      free(pair->key);
    }
    // if already freed, we don't want to double free
    free(pair);
  }
}
void shallow_destruct_my_string_int_pair(my_string_int_pair pair) {
  if (pair) {
    free(pair);
  }}
char *remove_punctuation(char *str) {
  unsigned long length = strlen(str);
  char* s;
  for (unsigned long i = 0; i < length; i++) {
    if (str[i] < 0) {
      s = remove_punctuation(str + i + 1);
      return s;
    }
    if (str[i] == ',' || str[i] == '.' || str[i] == ';' || str[i] == '!' || str[i] == ':') {
      str[i] = '\0';
      break;
    }
  }
  return str;
}

int main(int argc, char const *argv[]) {
  clock_t start = clock(), diff;
  char *tale = "tale.txt";
  FILE *fp_tale = fopen(tale, "r");
  if (!fp_tale) {
    perror("fopen");
    exit(EXIT_FAILURE);
  }

  struct stat sb;
  if (stat(tale, &sb) ==  -1) {
    perror("stat");
    exit(EXIT_FAILURE);
  }
  char *tale_contents = malloc(sb.st_size);
  my_string_int_rbt rbt_root = NULL;
  my_string_int_pair pair;
  char *t_str;
  char *str;

  while (fscanf(fp_tale, "%[^\n ] ", tale_contents) != EOF) {
    t_str = remove_punctuation(tale_contents);
    pair = find_in_my_string_int_rbt(rbt_root, t_str);

    if (!pair) {
      // its important to allocate a new str otherwise the tale_contents pointer will alone be referenced
      str = (char *)malloc(strlen(t_str) + 1); // i had done malloc(sizeof(strlen(t_str)) + 1), ASAN gave me heap overflow error
      strcpy(str, t_str);
      rbt_root = insert_my_string_int_rbt(rbt_root, str, 1);
    } else {
      // if the string str already exists, no point allocating it, otherwise there's going to be a memory leak
      rbt_root = insert_my_string_int_rbt(rbt_root, pair->key, pair->value + 1);
    }
  }
  int size = size_my_string_int_rbt(rbt_root);
  List_my_string_int_pair list = recursive_inorder_my_string_int_rbt(rbt_root);
  List_my_string_int_pair list0 = list;
  for (int i = 0; i < size; i++) {
    // printf("key = %s, value = %d\n", list->entry->key, list->entry->value);
    list = list->next;
  }
  shallow_destroy_List_my_string_int_rbt(list0, shallow_destruct_my_string_int_pair); // dont' call deep_destroy_List_my_string_int_rbt --
                                                // it will cause double free when calling free_whole_rbt_my_string_int_
                                                // since the keys are being shared between the list and the tree
  free_whole_rbt_my_string_int_(&rbt_root, destruct_my_string_int_pair);
  printf("size = %d\n", size_my_string_int_rbt(rbt_root));
  free(tale_contents);
  fclose(fp_tale);
  diff = clock() - start;
  int msec = diff * 1000 / CLOCKS_PER_SEC;
  printf("Time taken %d seconds %d milliseconds", msec/1000, msec%1000);
  return 0;
}
