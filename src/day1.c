#include <stdio.h>
#include "./utils.h"
#include <stdlib.h>

const int get_smallest(uint *used, uint *arr, ulong size){
  int small = -1;
  int final_index = -1;

  for(ulong i = 0; i<size;i++){
    //printf("%d ",arr[i]);
  }
    //printf("\n");

  for(int i = 0; i<size;i++){
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

const uint sum_split_diffs(Vec *left,Vec *right){
  uint sum = 0;
  uint *left_arr = vec_get_mem(left,uint);
  uint *right_arr = vec_get_mem(right,uint);
  uint *usedr = calloc(right->size,sizeof(uint));
  uint *usedl = calloc(left->size,sizeof(uint));

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

void split_line_to_sides(Vec *left, Vec*right,
                         const char *line, uint len){
  int start =-1 ; //start of spaces
  int end = -1; //end of spaces
  for(uint i = 0; i<len; i++){
    if(start == -1){
      if(line[i] == ' '){
        start = i;
      }
    }
    if(end == -1 && start != -1 && i > 0){
      if(line[i-1] == ' ' && line [i] != ' '){
        end = i;
      }
    }
  }
  char *leftstr = calloc(start,1);
  memcpy(leftstr, line, start);
  char *rightstr = calloc(len-end-1, 1);
  memcpy(rightstr, line+(len - (len -end)), len-end-1);
  uint leftnmr = atoi(leftstr);
  uint rightnmr = atoi(rightstr);
  free(leftstr);
  free(rightstr);
  //printf("%d->%d start: %d end: %d len; %d\n",
  //       leftnmr, rightnmr,start,end,len);

  vec_add(left, &leftnmr);
  vec_add(right, &rightnmr);
}

int main(int argc, char **argv){
  FILE *f = fopen(argv[1],"r");
  if(f== NULL){
    char msg[512];
    int size = snprintf(msg,512,"Couldn't open %s\n", argv[1]);
    perror(msg);
    return -1;
  }

  Vec *left = vec_new_typed(uint, 100);
  Vec *right = vec_new_typed(uint, 100);
  char *line = NULL;
  ulong width = 1024;

  long read = 0;
  while((read = getline(&line, &width, f)) && read != -1){
    split_line_to_sides(left,right,line, read);
  }

  const uint sum = sum_split_diffs(left,right);

  printf("SUM of Diffs %d\n",sum);
  fclose(f);
  vec_free(right);
  vec_free(left);
  return 0;
}
