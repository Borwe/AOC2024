#ifndef AOC_UTILS
#define AOC_UTILS 1

#include<stdlib.h>
#include<stdbool.h>
#include<string.h>

typedef struct Vec{
  unsigned size;
  void *memory;
  char *type;
  uint type_size;
  uint mem_size;
} Vec;

Vec *vec_new(unsigned count, char *typed, ulong type_size);
bool vec_will_fill_after_add(Vec *vec,int count);
void vec_grow(Vec *vec);
void vec_insert(Vec *vec, void *item);
void vec_free(Vec *vec);

#define vec_new_typed(type, count)\
  vec_new(count, #type, sizeof(type))

#define vec_get_mem(vec, type) (type *)vec->memory


/** Doubles memory if growing **/
#define vec_add(vec, item)\
  if(vec_will_fill_after_add(vec, 1)){\
    vec_grow(vec);\
  }\
  vec_insert(vec, (void *)item)

void vec_free(Vec *vec){
  free(vec->memory);
  free(vec);
}

void vec_insert(Vec *vec, void *item){
  void *start = vec->memory + (vec->size * vec->type_size);
  memcpy(start, item, vec->type_size);
  vec->size += 1;
}

/** Doubles memory **/
void vec_grow(Vec *vec){
  void *new_mem = malloc(vec->mem_size * 2);
  memset(new_mem,0,vec->mem_size*2);
  memcpy(new_mem, vec->memory, vec->mem_size * 2);
  free(vec->memory);
  vec->memory = new_mem;
  vec->mem_size *= 2;
}

bool vec_will_fill_after_add(Vec *vec,int count){
  const uint mem_after_add = ((vec->size+count)*vec->type_size);
  if(mem_after_add > vec->mem_size){
    return true;
  }
  return false;
}

void vec_clean(Vec *vec){
  memset(vec->memory,0,vec->mem_size);
  vec->size = 0;
}

Vec *vec_new(unsigned count, char *typed, ulong type_size){
  Vec *v = (Vec*)calloc(1, sizeof(Vec));
  v->memory = calloc(count, type_size);
  v->size = 0;
  v->mem_size = count * type_size;
  v->type = typed;
  v->type_size = type_size;
  return v;
}

#endif
