#include <stdio.h>
#include "./utils.h"

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
  char *leftstr = calloc(7,1);
  memcpy(leftstr, line, 7);
  char *rightstr = calloc(len-end, 1);
  memcpy(leftstr, line-end, len-end);
  printf("%s %s ->%s start: %d end: %d\n",line,leftstr, rightstr,start,end);
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

  printf("Opened %s",argv[1]);
  fclose(f);
  return 0;
}
