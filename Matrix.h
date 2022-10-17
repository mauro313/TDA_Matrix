#ifndef TDAMATRIX_H_INCLUDED
#define TDAMATRIX_H_INCLUDED

typedef struct{
 void** m;
 int rows;
 int columns;
}matrix_t;

matrix_t* matrix_new(int rows,int columns);

void matrix_free(matrix_t** mtrx);

int matrix_rows(matrix_t* mtrx);

int matrix_columns(matrix_t* mtrx);

void* matrix_get(matrix_t* mtrx,int row,int column);

void matrix_set(matrix_t* mtrx,int row,int column,void* value);

void matrix_printf(matrix_t* mtrx,void (*print)(void*));

#include "Matrix.c"
#endif // TDAMATRIX_H_INCLUDED
