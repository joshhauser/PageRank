#include <stdio.h>
#include "../headers/utils.h"

int index_in_vertices_array(Vertice *array, int array_length, int searched) {
  int i = 0;
  int index = -1;

  for (i = 0; i < array_length; i++)
    if (array[i].label == searched) return i;

  return i != array_length ? index : -1;
}

int index_in_int_array(int *array, int array_length, int searched) {
  int i = 0;
  int index = -1;

  for (i = 0; i < array_length; i++)
    if (array[i] == searched) return i;

  return i != array_length ? index : -1;
}