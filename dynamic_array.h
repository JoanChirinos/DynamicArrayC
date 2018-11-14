#ifndef DYNAMIC_ARRAY_H
#define DYNAMIC_ARRAY_H

struct dynamic_array {
  // The long long* SHOULD be typecasted to whatever you put in there
  long long* array;
  size_t size;
  size_t max_size;
};

struct dynamic_array* da_make_dynamic_array();

struct dynamic_array* da_make_dynamic_array_size(int);

struct dynamic_array* da_add(struct dynamic_array*, long long);

struct dynamic_array* da_add_at(struct dynamic_array*, long long, int);

struct dynamic_array* da_replace(struct dynamic_array*, long long, int);

struct dynamic_array* da_remove(struct dynamic_array*);

struct dynamic_array* da_remove_at(struct dynamic_array*, int);

struct dynamic_array* da_trim(struct dynamic_array*);

struct dynamic_array* da_free(struct dynamic_array*);

#endif
