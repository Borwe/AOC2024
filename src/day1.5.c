#include <stdio.h>
#include "./vec_utils.h"
#include <stdlib.h>

const uint sum_split_diffs(Vec *left,Vec *right){
  uint sum = 0;
  uint *left_arr = vec_get_mem(left,uint);
  uint *right_arr = vec_get_mem(right,uint);

  Vec *checked = vec_new_typed(uint,6);

  for(uint i = 0; i < left->size; i++ ){
    uint *chkd = vec_get_mem(checked, uint);
    bool already_chkd = false;
    for(uint j = 0; j< checked->size; j++){
      if(left_arr[i]==chkd[j]){
        already_chkd = true;
        break;
      }
    }

    if(already_chkd) continue;

    //chck for count
    uint counts = 0;
    for(uint j=0;j<right->size;j++){
      if(left_arr[i] == right_arr[j]){
        counts++;
      }
    }
    sum+=left_arr[i]*counts;
  }

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

  printf("SUM of times %d\n",sum);
  fclose(f);
  vec_free(right);
  vec_free(left);
  return 0;
}
