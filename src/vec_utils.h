#include <stdint.h>
#ifndef AOC_UTILS
#define AOC_UTILS 1

#include<stdlib.h>
#include<stdbool.h>
#include<string.h>
#include<stdio.h>

typedef struct Vec{
  unsigned size;
  void *memory;
  char *type;
  uint64_t type_size;
  uint64_t mem_size;
} Vec;

Vec *vec_new(unsigned count, char *typed, uint64_t type_size);
bool vec_will_fill_after_add(Vec *vec,int count);
void vec_grow(Vec *vec);
void vec_insert(Vec *vec, void *item);
void vec_free(Vec *vec);

#define vec_new_typed(type, count)\
  vec_new(count, #type, sizeof(type))

#define vec_get_mem(vec, type) (type *)vec->memory


/** Doubles memory if growing **/
void vec_add(Vec * const vec, void *item){
  if(vec_will_fill_after_add(vec, 1)){
    vec_grow(vec);
  }
  vec_insert(vec, (void *)item);
}

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
void vec_grow(Vec *const vec){
  void *new_mem = realloc(vec->memory, vec->mem_size*2);
  vec->memory = new_mem;
  vec->mem_size *= 2;
}

Vec *vec_clone(Vec *vec){
  Vec *vc = calloc(1, sizeof(Vec));
  vc->size = vec->size;
  vc->type_size = vec->type_size;
  vc->mem_size = vec->mem_size;
  vc->type = vec->type;
  vc->memory = malloc(vc->mem_size);
  memcpy(vc->memory,vec->memory,vc->mem_size);
  return vc;
}

void vec_remove(Vec *vec, void *d){
  void *end = vec->memory + (vec->size * vec->type_size);

  //printf("START: %p D: %p END: %p\n",
  //       vec->memory, d, end);
  if(d>=vec->memory && d <end){
    void *start = d + vec->type_size;
    memmove(d,start,end-start);
    vec->size -= 1;
    return;
  }
  if(d == end){
    vec->size -=1;
    return;
  }

  printf("WTF DIDN't DO SHIT!!!\n");
}

bool vec_will_fill_after_add(Vec * const vec,int count){
  const uint64_t mem_after_add = ((vec->size+count)*vec->type_size);
  if(mem_after_add > vec->mem_size){
    return true;
  }
  return false;
}

void vec_clean(Vec *vec){
  memset(vec->memory,0,vec->mem_size);
  vec->size = 0;
}

Vec *vec_new(unsigned count, char *typed, uint64_t type_size){
  Vec *v = (Vec*)calloc(1, sizeof(Vec));
  v->memory = calloc(count, type_size);
  v->size = 0;
  v->mem_size = count * type_size;
  v->type = typed;
  v->type_size = type_size;
  return v;
}

#endif
