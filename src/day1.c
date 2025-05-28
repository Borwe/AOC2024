#include <stdint.h>
#include <stdio.h>
#include "./vec_utils.h"
#include <stdlib.h>
#include <string.h>

int get_smallest(uint64_t *used, int64_t *arr, uint64_t size){
  int small = -1;
  int final_index = -1;

  for(uint64_t i = 0; i<size;i++){
    //printf("%d ",arr[i]);
  }
    //printf("\n");

  for(uint64_t i = 0; i<size;i++){
    if(small == -1 && used[i] != 1){
      small = arr[i];
      final_index = i;
      //printf("SET S: %d\n",small);
    }

    if(small!= -1 && small > arr[i] && used[i] != 1){
      small = arr[i];
      final_index = i;
      //printf("FOUND %d fin: %d\n",small, final_index);
    }
  }

  //meaning no unused small
  if(final_index==-1){
    return -1;
  }
  used[final_index] = 1;
  return small;
}

uint64_t sum_split_diffs(Vec *left,Vec *right){
  uint64_t sum = 0;
  int64_t *left_arr = vec_get_mem(left,int64_t);
  int64_t *right_arr = vec_get_mem(right,int64_t);
  uint64_t *usedr = calloc(right->size,sizeof(uint64_t));
  uint64_t *usedl = calloc(left->size,sizeof(uint64_t));

  bool all_usedl = false;

  while(!all_usedl){
    const int smalll = get_smallest(usedl,left_arr, left->size);
    const int smallr = get_smallest(usedr,right_arr, right->size);
    //printf("l: %d r: %d ls: %d rs: %d\n",smalll,smallr, left->size, right->size);
    if(smalll == -1 || smallr == -1){
      all_usedl = true;
      continue;
    }
    sum += abs(smalll-smallr);
  }

  free(usedr);
  free(usedl);
  return sum;
}

void split_line_to_sides(Vec *left, Vec*right, const char *line, uint64_t len){
  int start =-1 ; //start of spaces
  int end = -1; //end of spaces
  for(uint64_t i = 0; i<len; i++){
    if(start == -1){
      if(line[i] == ' '){
        start = i;
      }
    }
    if(end == -1 && start != -1 && i > 0){
      if(i > 0 && line[i-1] == ' ' && line [i] != ' '){
        end = i;
      }
    }
  }
  char *leftstr = calloc(start+1,1);
  memcpy(leftstr, line, start);
  char *rightstr = calloc(len-end, 1);
  memcpy(rightstr, line+(len - (len -end)), len-end-1);
  uint64_t leftnmr = atoi(leftstr);
  uint64_t rightnmr = atoi(rightstr);
  free(leftstr);
  free(rightstr);
  //printf("%d->%d start: %d end: %d len; %d\n",
  //       leftnmr, rightnmr,start,end,len);

  vec_add(left, &leftnmr);
  vec_add(right, &rightnmr);
}

int main(int argc , char **argv){
  (void)argc;
  FILE *f = fopen(argv[1],"r");
  if(f== NULL){
    char msg[512];
    snprintf(msg,512,"Couldn't open %s\n", argv[1]);
    perror(msg);
    return -1;
  }

  Vec *left = vec_new_typed(uint64_t, 100);
  Vec *right = vec_new_typed(uint64_t, 100);
  const uint64_t width = 1024;
  char line_buf[width] ;

  char *line = NULL;
  
  while((line = fgets(line_buf, width, f)) && line != NULL){
    const int read = strlen(line);
    split_line_to_sides(left,right,line, read);
  }

  const uint64_t sum = sum_split_diffs(left,right);

  printf("SUM of Diffs %lu\n",sum);
  fclose(f);
  vec_free(right);
  vec_free(left);
  return 0;
}
