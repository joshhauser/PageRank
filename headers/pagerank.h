#ifndef PAGERANK_H
#define PAGERANK_H

#include "../headers/matrix.h"

Vector apply_pagerank(Matrix matrix, double d, double epsilon);

#endif