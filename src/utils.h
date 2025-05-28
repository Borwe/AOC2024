#include <stdbool.h>
#ifndef AOC_UTILS
#define AOC_UTILS 1

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct Lines {
  uint64_t line_size;
  char *line;
  FILE *file;
}Lines;

/* Returns line, returned value is null if no more lines */
char *utils_next_line(Lines *const lines){
  return fgets(lines->line, lines->line_size, lines->file);
}

Lines utils_prepare_read_lines_from_file(char *file, uint64_t line_size){
  Lines lines = {
    .line_size = line_size,
    .line = calloc(line_size, 1)
  };

  FILE *f = fopen(file, "r");
  if(!f){
    char msg[512];
    snprintf(msg, 512, "Couldn't open %s\n", file);
    perror(msg);
    exit(-1);
  }

  lines.file = f;
  return lines;
}

void utils_free_lines(Lines * const lines){
  if(lines->line != NULL){
    free(lines->line);
  }
  if(lines->file != NULL) {
    fclose(lines->file);
  }
}

#endif
