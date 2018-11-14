#include <stdio.h>
#include <stdlib.h>

struct dynamic_array {
  // The long long* SHOULD be typecasted to whatever you put in there
  long long* array;
  size_t size;
  size_t max_size;
};

/*
For printing:

int print_counter = 0;
int print_to = <ARRAY_NAME>->size;
for ( ; print_counter < print_to; print_counter += 1) {
  printf("<FORMATTING OPTION>, ", (<ARRAY TYPE>)(*(<ARRAY_NAME>->array + print_counter)));
}
printf("\n");

*/

struct dynamic_array* da_make_dynamic_array() {
  struct dynamic_array* d_arr = calloc(sizeof(struct dynamic_array), 1);
  d_arr->array = calloc(sizeof(long long), 10);
  d_arr->size = 0;
  d_arr->max_size = 10;
  return d_arr;
}

struct dynamic_array* da_make_dynamic_array_size(int arr_max_size) {
  struct dynamic_array* d_arr = calloc(sizeof(struct dynamic_array), 1);
  d_arr->array = calloc(sizeof(long long), arr_max_size);
  d_arr->size = 0;
  d_arr->max_size = arr_max_size;
  return d_arr;
}

struct dynamic_array* da_add(struct dynamic_array* d_arr, long long x) {
  if (d_arr->size == d_arr->max_size) {
    // double array size
    long long* new_array = calloc(sizeof(long long), (d_arr->max_size * 2));
    int i_at;
    int max_i = d_arr->size;
    for (i_at = 0; i_at < max_i; i_at += 1) {
      *(new_array + i_at) = *(d_arr->array + i_at);
    }
    free(d_arr->array);
    d_arr->array = new_array;
    d_arr->max_size *= 2;
  }
  *(d_arr->array + d_arr->size) = x;
  d_arr->size += 1;
  return d_arr;
}

struct dynamic_array* da_add_at(struct dynamic_array* d_arr, long long x, int index) {
  if (index >= d_arr->size || index < 0) {
    printf("out of bounds\n");
    return d_arr;
  }
  if (d_arr->size == d_arr->max_size) {
    // double array size
    long long* new_array = calloc(sizeof(long long), (d_arr->max_size * 2));
    int i_at;
    int max_i = d_arr->size;
    for (i_at = 0; i_at < max_i; i_at += 1) {
      *(new_array + i_at) = *(d_arr->array + i_at);
    }
    free(d_arr->array);
    d_arr->array = new_array;
    d_arr->max_size *= 2;
  }
  // algo for adding then shifting

  long long temp = x;
  int max = d_arr->size + 1;
  for ( ; index < max; index++) {
    *(d_arr->array + index) ^= temp;
    temp ^= *(d_arr->array + index);
    *(d_arr->array + index) ^= temp;
  }
  d_arr->size += 1;
  return d_arr;
}

struct dynamic_array* da_replace(struct dynamic_array* d_arr, long long x, int index) {
  if (index >= d_arr->size || index < 0) {
    printf("out of bounds\n");
    return d_arr;
  }
  *(d_arr->array + index) = x;
  return d_arr;
}

struct dynamic_array* da_remove(struct dynamic_array* d_arr) {
  if (d_arr->size == 0) {
    printf("dynamic_array is size 0\n");
    return d_arr;
  }
  d_arr->size -= 1;
  return d_arr;
}

struct dynamic_array* da_remove_at(struct dynamic_array* d_arr, int index) {
  if (d_arr->size == 0) {
    printf("dynamic_array is size 0\n");
    return d_arr;
  }
  if (index >= d_arr->size || index < 0) {
    printf("out of bounds\n");
    return d_arr;
  }
  int max = d_arr->size;
  for ( ; index < max; index++) {
    *(d_arr->array + index) = *(d_arr->array + index + 1);
  }
  d_arr->size -= 1;
  return d_arr;
}

struct dynamic_array* da_trim(struct dynamic_array* d_arr) {
  int size = d_arr->size;
  struct dynamic_array* new_arr = da_make_dynamic_array_size(size);
  int index;
  for (index = 0; index < size; index++) {
    *(new_arr->array + index) = *(d_arr->array + index);
    new_arr->size += 1;
  }
  free(d_arr->array);
  free(d_arr);
  return new_arr;
}

struct dynamic_array* da_free(struct dynamic_array* d_arr) {
  free(d_arr->array);
  free(d_arr);
  return (struct dynamic_array*)NULL;
}

int main() {
  int print_counter;
  int print_to;
  struct dynamic_array* d_arr = da_make_dynamic_array();
  int i;
  for (i = 0; i < 15; i++) {
    d_arr = da_add(d_arr, i);
    // int print_counter = 0;
    // int print_to = d_arr->size;
    // for ( ; print_counter < print_to; print_counter += 1) {
    //   printf("%d, ", (int)(*(d_arr->array + print_counter)));
    // }
    // printf("\n");
  }

  // printing
  // print_counter = 0;
  // print_to = d_arr->size;
  // for ( ; print_counter < print_to; print_counter += 1) {
  //   printf("%d, ", (int)(*(d_arr->array + print_counter)));
  // }
  // printf("\n");

  // removing couple last elements
  for (i = 0; i < 3; i++) {
    d_arr = da_remove(d_arr);
  }

  // print_counter = 0;
  // print_to = d_arr->size;
  // for ( ; print_counter < print_to; print_counter += 1) {
  //   printf("%d, ", (int)(*(d_arr->array + print_counter)));
  // }
  // printf("\n");

  // adding some elements at end

  for (i = 6; i < 9; i++) {
    d_arr = da_add(d_arr, i);
  }

  // printf("BEFORE:\n");
  // print_counter = 0;
  // print_to = d_arr->size;
  // for ( ; print_counter < print_to; print_counter += 1) {
  //   printf("%d, ", (int)(*(d_arr->array + print_counter)));
  // }
  // printf("\n");

  for (i = 4; i >= 0; i--) {
    d_arr = da_add_at(d_arr, i, 2);
    // print_counter = 0;
    // print_to = d_arr->size;
    // for ( ; print_counter < print_to; print_counter += 1) {
    //   printf("%d, ", (int)(*(d_arr->array + print_counter)));
    // }
    // printf("\n");
  }

  print_counter = 0;
  print_to = d_arr->size;
  for ( ; print_counter < print_to; print_counter += 1) {
    printf("%d, ", (int)(*(d_arr->array + print_counter)));
  }
  printf("\n");

  for (i = 0; i < 5; i++) {
    d_arr = da_remove_at(d_arr, 2);
    print_counter = 0;
    print_to = d_arr->size;
    for ( ; print_counter < print_to; print_counter += 1) {
      printf("%d, ", (int)(*(d_arr->array + print_counter)));
    }
    printf("\n");
  }
  for (i = 0; i < 3; i++) {
    d_arr = da_remove_at(d_arr, d_arr->size - 1);
    print_counter = 0;
    print_to = d_arr->size;
    for ( ; print_counter < print_to; print_counter += 1) {
      printf("%d, ", (int)(*(d_arr->array + print_counter)));
    }
    printf("\n");
  }

  printf("d_arr:\n\t");
  print_counter = 0;
  print_to = d_arr->size;
  for ( ; print_counter < print_to; print_counter += 1) {
    printf("%d, ", (int)(*(d_arr->array + print_counter)));
  }
  printf("\n");
  printf("\tsize: %d\n\tmax size: %d\n", (int)d_arr->size, (int)d_arr->max_size);

  d_arr = da_trim(d_arr);
  printf("\nd_arr AFTER TRIM:\n\t");
  print_counter = 0;
  print_to = d_arr->size;
  for ( ; print_counter < print_to; print_counter += 1) {
    printf("%d, ", (int)(*(d_arr->array + print_counter)));
  }
  printf("\n");
  printf("\tsize: %d\n\tmax size: %d\n", (int)d_arr->size, (int)d_arr->max_size);

  printf("\nKilling d_arr\n");
  d_arr = da_free(d_arr);
  printf("d_arr pointer: %p\n", d_arr);

  return 0;
}
