#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "matrix.h"

Matrix get_matrix_from_file(char *file_path, int length) {
  FILE *fp;
  char *line = NULL;
  size_t len = 0;
  ssize_t read;
  Matrix matrix;
  int value = 0;
  int i = 0;
  int k = 0;

  fp = fopen(file_path, "r");
  if (fp == NULL) {
    printf("Fichier introuvable.");
    exit(EXIT_FAILURE);
  }

  matrix.lines_number = length;
  matrix.colums_number = length;
  allocate_matrix(&matrix);

  while ((read = getline(&line, &len, fp)) != -1) {
    sscanf(&line[0], "%d", &value);
    printf("Val : %d\n", value);

    int index = (int)(strchr(line, ' ') - line);
    sscanf(&line[index+1], "%d", &value);
    printf("Val : %d\n", value);
    printf("------------------\n");

    i++;
  }

  printf("[END] i = %d\n", i);

  return matrix;
}