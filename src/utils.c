#include <stdio.h>
#include "../headers/utils.h"

/**
 * @brief Find the index of a Vertice
 * in an array
 * 
 * @param array the vertices array used for element searching 
 * @param array_length the array length
 * @param searched the element to search
 * @return the index of the Vertice if it exists in the array,
 * otherwise -1
 */
int index_in_vertices_array(Vertice *array, int array_length, int searched) {
  int i = 0;

  for (i = 0; i < array_length; i++)
    if (array[i].label == searched) return i;

  return -1;
}

/**
 * @brief Find the index of an integer
 * in an array
 * 
 * @param array the int array used for element searching 
 * @param array_length the array length
 * @param searched the element to search
 * @return the index of the integer if it exists in the array,
 * otherwise -1
 */
int index_in_int_array(int *array, int array_length, int searched) {
  int i = 0;

  for (i = 0; i < array_length; i++)
    if (array[i] == searched) return i;

  return -1;
}

/**
 * @brief Function used in qsort()
 * to sort an array of double
 * by comparing two elements.
 * Elements are sorted in reverse order.
 * 
 * @param first the first element to compare
 * @param second the second to compare
 * @return int that's -1 if first > second,
 * 1 if first < second, 0 otherwise
 */
int compare_doubles(const void* first, const void* second) {
  double a = *(const double*) first;
  double b = *(const double*) second;

  return a > b ? - 1 : a < b ? 1 : 0;
}