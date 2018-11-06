#include <stdio.h>
#include <stdlib.h>

#include "super_array.h"

struct super_array {
  int* array;
  int size;
  int max_size;
};

struct super_array* make_super_array() {
  struct super_array* s_arr = calloc(sizeof(struct super_array), 1);
  s_arr->array = calloc(sizeof(int), 10);
  s_arr->size = 0;
  s_arr->max_size = 10;
  return s_arr;
}

struct super_array* make_super_array_with_size(int size) {
  struct super_array* s_arr = calloc(sizeof(struct super_array), 1);
  s_arr->array = calloc(sizeof(int), size);
  s_arr->size = 0;
  s_arr->max_size = size;
  return s_arr;
}

int get_from_array(struct super_array* s_arr, int index) {
  if (index >= s_arr->size || index < 0) {
    printf("invalid index\n");
    return 0;
  }
  return *(s_arr->array + index);
}

struct super_array* add_to_array(struct super_array* s_arr, int new_int) {
  // if you'd break boundary of calloc, expand
  if (s_arr->size + 1 >= s_arr->max_size) {
    int* new = calloc(sizeof(int), s_arr->max_size * 2);
    int ctr;
    for (ctr = 0; ctr < s_arr->size; ctr += 1) {
      *(new + ctr) = get_from_array(s_arr, ctr);
    }
    free(s_arr->array);
    s_arr->array = new;
    s_arr->max_size *= 2;
  }
  // then add to the end
  *(s_arr->array + s_arr->size) = new_int;
  s_arr->size += 1;
  return s_arr;
}

struct super_array* remove_last_element(struct super_array* s_arr) {
  s_arr->size -= 1;
  return s_arr;
}

struct super_array* add_to_array_at(struct super_array* s_arr, int index, int new_int) {
  // if you try to break it, don't
  if (index >= s_arr->size) {
    printf("invalid index. returning array unchanged\n");
    return s_arr;
  }
  // if you'd break boundary of calloc, expand
  if (s_arr->size + 1 >= s_arr->max_size) {
    s_arr->array = realloc(s_arr->array, s_arr->max_size * 2);
    s_arr->max_size *= 2;
  }

  s_arr->size += 1;

  int mem = new_int;
  while (index < s_arr->size) {
    int temp = get_from_array(s_arr, index);
    *(s_arr->array + index) = mem;
    mem = temp;
    index += 1;
  }

  return s_arr;
}

struct super_array* replace_element_at(struct super_array* s_arr, int index, int new_int) {
  // if you try to break it, don't
  if (index >= s_arr->size) {
    printf("invalid index. returning array unchanged\n");
    return s_arr;
  }
  *(s_arr->array + index) = new_int;
  return s_arr;
}

struct super_array* remove_element_at(struct super_array* s_arr, int index) {
  // if you try to break it, don't
  if (index >= s_arr->size) {
    printf("invalid index. returning array unchanged\n");
    return s_arr;
  }
  if (index == s_arr->size - 1) {
    return remove_last_element(s_arr);
  }
  while (index + 1 < s_arr->size) {
    *(s_arr->array + index) = get_from_array(s_arr, index + 1);
    index += 1;
  }
  s_arr->size -= 1;
  return s_arr;
}

struct super_array* remove_value(struct super_array* s_arr, int val) {
  int index;
  for (index = 0; index < s_arr->size; index += 1) {
    if (get_from_array(s_arr, index) == val) {
      s_arr = remove_element_at(s_arr, index);
      break;
    }
  }
  return s_arr;
}

int contains(struct super_array* s_arr, int val) {
  int index = 0;
  for ( ; index < s_arr->size; index += 1) {
    if (get_from_array(s_arr, index) == val) return 1;
  }
  return 0;
}

struct super_array* trim(struct super_array* s_arr) {
  struct super_array* new = make_super_array_with_size(s_arr->size);
  int ctr;
  for (ctr = 0; ctr < s_arr->size; ctr += 1) {
    *(new->array + ctr) = get_from_array(s_arr, ctr);
    new->size += 1;
  }
  s_arr = delete_super_array(s_arr);
  return new;
}

int is_empty(struct super_array* s_arr, int val) {
  return s_arr->size != 0;
}

void print_super_array(struct super_array* s_arr) {
  if (s_arr->size == 0) {
    printf("[]\n");
    return;
  }
  int size = s_arr->size;
  int current;
  printf("[");
  for (current = 0; current < size - 1; current += 1) {
    printf("%d, ", *(s_arr->array + current));
  }
  printf("%d]\n", *(s_arr->array + current));
}

void* delete_super_array(struct super_array* s_arr) {
  int* arr = s_arr->array;
  free(s_arr);
  free(arr);
  return NULL;
}

int main() {
  struct super_array* s_arr = make_super_array();
  int i;
  printf("adding els [0, 15) to array\n");
  for (i = 0; i < 15; i += 1) {
    s_arr = add_to_array(s_arr, i);
    print_super_array(s_arr);
  }

  printf("\nadding 492 at index 4\n");
  s_arr = add_to_array_at(s_arr, 4, 492);
  print_super_array(s_arr);

  printf("\nreplacing el at index 4 with 9\n");
  s_arr = replace_element_at(s_arr, 4, 9);
  print_super_array(s_arr);

  printf("removing element at index 4\n");
  s_arr = remove_element_at(s_arr, 4);
  print_super_array(s_arr);

  printf("removing element at index 0 until array is empty\n");
  while (s_arr->size >= 1) {
    s_arr = remove_element_at(s_arr, 0);
    print_super_array(s_arr);
  }

  printf("\nadding back elements from 1 to 15\n");
  for (i = 1; i <= 15; i++) {
    s_arr = add_to_array(s_arr, i);
    print_super_array(s_arr);
  }

  printf("array contains 5: %d\n", contains(s_arr, 5));
  printf("array contains 16: %d\n", contains(s_arr, 16));

  printf("removing last element 4 times\n");
  for (i = 0; i < 4; i++) {
    s_arr = remove_last_element(s_arr);
    print_super_array(s_arr);
  }

  printf("size of array: %d\n", s_arr->size);
  printf("max size of array: %d\n", s_arr->max_size);

  printf("trimming array\n");
  s_arr = trim(s_arr);

  print_super_array(s_arr);

  printf("size of array: %d\n", s_arr->size);
  printf("max size of array: %d\n", s_arr->max_size);

  s_arr = delete_super_array(s_arr);
  return 0;
}
