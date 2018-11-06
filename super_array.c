#include <stdio.h>
#include <stdlib.h>

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
    for (ctr = 0; ctr < s_arr->size; ctr++) {
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
    index++;
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

void print_super_array(struct super_array* s_arr) {
  int size = s_arr->size;
  int current;
  printf("[");
  for (current = 0; current < size - 1; current++) {
    printf("%d, ", *(s_arr->array + current));
  }
  printf("%d]\n", *(s_arr->array + current));
}

void* delete_array(struct super_array* s_arr) {
  free(s_arr);
  free(s_arr->array);
  return NULL;
}

int main() {
  struct super_array* s_arr = make_super_array();
  int i;
  printf("adding els [0, 15) to array\n");
  for (i = 0; i < 15; i++) {
    s_arr = add_to_array(s_arr, i);
    print_super_array(s_arr);
  }

  printf("\nadding 492 at index 4\n");
  s_arr = add_to_array_at(s_arr, 4, 492);
  print_super_array(s_arr);

  printf("\nreplacing el at index 4 with 9\n");
  s_arr = replace_element_at(s_arr, 4, 9);
  print_super_array(s_arr);

  s_arr = delete_array(s_arr);
  return 0;
}
