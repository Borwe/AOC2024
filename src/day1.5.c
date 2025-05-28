#include <stdint.h>
#include <stdio.h>
#include "./vec_utils.h"
#include "./utils.h"
#include <stdlib.h>
#include <string.h>

uint64_t sum_split_diffs(Vec *left,Vec *right){
  uint64_t sum = 0;
  uint64_t *left_arr = vec_get_mem(left,uint64_t);
  uint64_t *right_arr = vec_get_mem(right,uint64_t);

  Vec *checked = vec_new_typed(uint64_t,6);

  for(uint64_t i = 0; i < left->size; i++ ){
    uint64_t *chkd = vec_get_mem(checked, uint64_t);
    bool already_chkd = false;
    for(uint64_t j = 0; j< checked->size; j++){
      if(left_arr[i]==chkd[j]){
        already_chkd = true;
        break;
      }
    }

    if(already_chkd) continue;

    //chck for count
    uint64_t counts = 0;
    for(uint64_t j=0;j<right->size;j++){
      if(left_arr[i] == right_arr[j]){
        counts++;
      }
    }
    sum+=left_arr[i]*counts;
  }

  vec_free(checked);

  return sum;
}

void split_line_to_sides(Vec *left, Vec*right,
                         const char *line, uint64_t len){
  int start =-1 ; //start of spaces
  int end = -1; //end of spaces
  for(uint64_t i = 0; i<len; i++){
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

int main(int argc, char **argv){
  (void)argc;
  Lines lines = utils_prepare_read_lines_from_file(argv[1], 512);

  Vec *left = vec_new_typed(uint64_t, 100);
  Vec *right = vec_new_typed(uint64_t, 100);

  char *line = NULL;
  while((line = utils_next_line(&lines)) && line != NULL){
    uint64_t read = strlen(line);;
    split_line_to_sides(left,right,line, read);
  }

  const uint64_t sum = sum_split_diffs(left,right);

  printf("SUM of times %lu\n",sum);
  utils_free_lines(&lines);
  vec_free(right);
  vec_free(left);
  return 0;
}
