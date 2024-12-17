#include<ctype.h>
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include"vec_utils.h"

int get_mults(char *line, ulong width, bool *enabled){
  int result =0;

  static const char *mul = "mul(";
  static const char *dos = "do()";
  static const char *donts = "don\'t()";

  Vec *numchar1 = vec_new_typed(char, 3);
  Vec *numchar2= vec_new_typed(char, 3);


  for(uint i = 0; i< width; i++){
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
      for(int j = i;j<width; j++,i=j){
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
  FILE *f = fopen(argv[1], "r");
  if(f==NULL){
    char msg[512];
    int size = snprintf(msg,512,"Couldn't open %s\n", argv[1]);
    perror(msg);
    return -1;
  }

  char *line = NULL;
  ulong width = 1024 * 1024 * 1024;
  int read = -1;

  int sum = 0;
  bool enabled = true;
  while((read = getline(&line, &width, f)) && read != -1){
    sum += get_mults(line,read, &enabled);
    //printf("LINE: %s",line);
  }

  printf("SUMS: %d\n",sum);
  fclose(f);

  return 0;
}
