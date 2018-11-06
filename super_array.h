#ifndef SUPER_ARRAY_H
#define SUPER_ARRAY_H

struct super_array* make_super_array();

struct super_array* make_super_array_with_size(int);

int get_from_array(struct super_array*, int);

struct super_array* add_to_array(struct super_array*, int);

struct super_array* remove_last_element(struct super_array*);

struct super_array* add_to_array_at(struct super_array*, int, int);

struct super_array* replace_element_at(struct super_array*, int, int);

struct super_array* remove_element_at(struct super_array*, int);

struct super_array* remove_value(struct super_array*, int);

int contains(struct super_array*, int);

struct super_array* trim(struct super_array*);

int is_empty(struct super_array*, int);

void print_super_array(struct super_array*);

void* delete_super_array(struct super_array*);

#endif
