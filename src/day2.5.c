#include<stdio.h>
#include<ctype.h>
#include<stdlib.h>
#include<stdbool.h>
#include"vec_utils.h"
#include "./utils.h"

Vec *get_nums(const char *line,const uint64_t len){
  Vec *nums = vec_new_typed(int, 10);
  Vec *num = vec_new_typed(char,10);
  for(uint64_t i=0; i< len; i++){
    if(i>0 && line[i]==' ' && isdigit(line[i-1])){
      //we have reached a number
      int n = atoi(vec_get_mem(num,char));
      vec_add(nums,&n);
      vec_clean(num);
    }

    if(isdigit(line[i])){
      vec_add(num,(void*)&line[i]);
    }
  }
  int n = atoi(vec_get_mem(num,char));
  vec_add(nums,&n);
  vec_free(num);
  return nums;
}

bool check_if_valid(const char *line,const int len){
  Vec *nums = get_nums(line, len);
  Vec *real = nums; // keep location of the real
  bool answer = true;
  bool first_retry = false;
  //hold index of item to be removed
  uint64_t indx = 0;

  //use go to to come here and clone num and
  //retry with removed indx item
  remove_item:
  if(real != nums){
    vec_free(nums);
  }
  nums = vec_clone(real);
  int *nms = vec_get_mem(nums, int);
  if(!answer){
    //before
    vec_remove(nums,&nms[indx]);
    nms = vec_get_mem(nums, int);
    answer = true;
  }

  bool is_acc = nums->size>0?nms[0]<nms[1]:false;
  for(uint64_t i=0;i<nums->size; i++){
    if(is_acc && i>0 && nms[i-1] > nms[i]){
      answer = false;
      break;
    }
    if(!is_acc && i>0 && nms[i-1] < nms[i]){
      answer = false;
      break;
    }
    if(i>0){
      int diff = is_acc? nms[i]-nms[i-1] : nms[i-1]-nms[i];
      if( diff < 1 || diff > 3){
        answer = false;
        break;
      }
    }
  }

  if(!answer && indx < real->size-1){
    if(!first_retry){
      first_retry = true;
    }else{
      indx+=1;
    }
    goto remove_item;
  }

  vec_free(real);
  vec_free(nums);
  return answer;
}

int main(int argc, char **argv){
  (void)argc;
  Lines lines = utils_prepare_read_lines_from_file(argv[1], 1024);

  char *line = NULL;
  int read = -1;

  uint64_t valids = 0;
  while((line = utils_next_line(&lines)) && line != NULL){
    read = strlen(line);
    if(check_if_valid(line, read)) valids++;
    read = -1;
  }

  printf("Valid reports: %lu\n",valids);
  utils_free_lines(&lines);
  return 0;
}
