#include<ctype.h>
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include <string.h>
#include "./vec_utils.h"
#include "./utils.h"

int get_mults(char *line, uint64_t width, bool *enabled){
  int result =0;

  static const char *mul = "mul(";
  static const char *dos = "do()";
  static const char *donts = "don\'t()";

  Vec *numchar1 = vec_new_typed(char, 4);
  Vec *numchar2= vec_new_typed(char, 4);


  for(uint64_t  i = 0; i< width; i++){
    if(memcmp(line+i,donts,7) == 0){
      *enabled = false;
    }else if(memcmp(line+i,dos,4) == 0){
      *enabled = true;
    }else if(memcmp(line+i,mul,4) == 0 && *enabled){
      i+=4;
      if(!*enabled){
        continue;
      }
      bool comma = false;
      for(uint64_t j = i;j<width; j++,i=j){
        if(*(line+j)==','){
          comma = true;
          continue;
        }
        if(isdigit(*(line+j))){
          if(comma){
            vec_add(numchar2,line+j);
          }else{
            vec_add(numchar1,line+j);
          }
          continue;
        }
        //break, shouldn't reach here
        break;
      }
      if(*(line+i)==')' && numchar1->size <= 3 && numchar2->size <= 3){
        int left = atoi(vec_get_mem(numchar1,char));
        int right = atoi(vec_get_mem(numchar2,char));
        //printf("got: %d, %d\n",left,right);
        result=result + (left*right);
      }
    }
    vec_clean(numchar1);
    vec_clean(numchar2);
  }
  vec_free(numchar1);
  vec_free(numchar2);
  return result;
}

int main(int argc, char **argv){
  (void)argc;
  Lines lines = utils_prepare_read_lines_from_file(argv[1], 1024*1024*1024);

  char *line = NULL;
  int read = -1;

  int sum = 0;
  bool enabled = true;
  while((line = utils_next_line(&lines)) && line != NULL){
    read = strlen(line);
    sum += get_mults(line,read, &enabled);
    read = -1;
    //printf("LINE: %s",line);
  }

  printf("SUMS: %d\n",sum);
  utils_free_lines(&lines);

  return 0;
}
