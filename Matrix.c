#include <stdio.h>
#include <stdlib.h>
#include "Matrix.h"

//Se reserva memoria para una nueva matriz
matrix_t* matrix_new(int rows,int columns){
  matrix_t* matrix = (matrix_t*)malloc(sizeof(matrix_t));
  if(matrix == NULL){
    printf("memory cannot be reserved\n");
    exit(-1);
  }
  else{
    matrix->m =(void**)malloc((rows*columns)*sizeof(void*));
    if(matrix->m == NULL){
      free(matrix);
      matrix = NULL;
      printf("memory cannot be reserved\n");
      exit(-2);
    }
    else{
      matrix->rows = rows;
      matrix->columns = columns;
    }
  }
  return matrix;
}

//Se libera la memoria de la matriz
void matrix_free(matrix_t** mtrx){
  if(mtrx != NULL && *mtrx != NULL){
    free((*mtrx)->m);
    (*mtrx)->m = NULL;
    free(*mtrx);
    *mtrx = NULL;
  }
}

//Retorna las filas
int matrix_rows(matrix_t* mtrx){
  if(mtrx == NULL){
    printf("matrix pointer is NULL");
    exit(-3);  
  }
  return mtrx->rows;
}

//Retorna las columnas
int matrix_columns(matrix_t* mtrx){
  if(mtrx == NULL){
    printf("matrix pointer is NULL");
    exit(-4);  
  }
  return mtrx->columns;
}

//Retorna el elemento seleccionado
void* matrix_get(matrix_t* mtrx,int row,int column){
  if(mtrx == NULL){
    printf("matrix pointer is NULL");
    exit(-5);
  }
  return mtrx->m[row*matrix_columns(mtrx)+column];
}

//Agrega un elemento a la matriz en la fila y columna seleccionada
void matrix_set(matrix_t* mtrx,int row,int column,void* value){
  if(mtrx == NULL){
    printf("matrix pointer is NULL");
    exit(-6);    
  }
  mtrx->m[row*matrix_columns(mtrx)+column] = value;
}

//Imprime la matriz
void matrix_printf(matrix_t* mtrx,void(*print)(void*)){
  if(mtrx == NULL){
    printf("matrix pointer is NULL");
    return;
  }
  for(int i=0;i<matrix_rows(mtrx);i++){
    for(int j=0;j<matrix_columns(mtrx);j++){
       print(mtrx->m[i*matrix_columns(mtrx)+j]);
       if(j == matrix_columns(mtrx)-1)
        printf("\n");
    }
  }
}



