#include "graph.h"
#include "utils.h"

int index_in_array(Vertice *array, int array_length, int searched) {
  int i;
  int index = -1;

  for (i = 0; array[i].label != searched && i < array_length; i++) index = i;
  //for (i = 0; i < array; i++) if (array[i] < searched) index = i;
  
  return i != array_length ? i : -1;
}