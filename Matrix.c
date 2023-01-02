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
  matrix->m =(void**)malloc((rows*columns)*sizeof(void*));
  if(matrix->m == NULL){
    free(matrix);
    matrix = NULL;
    printf("memory cannot be reserved\n");
    exit(-2);
  }
  for(int i=0;i<rows;i++){
    for(int j=0;j<columns;j++){
      matrix->m[i*columns+j] = NULL;  
    }  
  }
  matrix->rows = rows;
  matrix->columns = columns;
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

//Retorna el elemento seleccionado por fila o columna.
void* matrix_get(matrix_t* mtrx,int row,int column){
  if(mtrx == NULL){
    printf("matrix pointer is NULL");
    exit(-5);
  }
  if(row<0 || row>=mtrx->rows){
    printf("invalid row");
    exit(-6);  
  }
  if(column<0 || column>=mtrx->columns){
    printf("invalid column");
    exit(-7);
  }
  return mtrx->m[row*mtrx->columns+column];
}

//Agrega un elemento a la matriz en la fila y columna seleccionada.
void matrix_set(matrix_t* mtrx,int row,int column,void* value){
  if(mtrx == NULL){
    printf("matrix pointer is NULL");
    exit(-8);    
  }
  if(row<0 || row>=mtrx->rows){
    printf("invalid row");
    exit(-9);  
  }
  if(column<0 || column>=mtrx->columns){
    printf("invalid column");
    exit(-10);
  }
  mtrx->m[row*mtrx->columns+column] = value;
}

//Imprime la matriz
void matrix_printf(matrix_t* mtrx,void(*print)(void*)){
  if(mtrx == NULL){
    printf("matrix pointer is NULL");
    exit(-11);
  }
  for(int i=0;i<matrix_rows(mtrx);i++){
    for(int j=0;j<matrix_columns(mtrx);j++){
       print(mtrx->m[i*matrix_columns(mtrx)+j]);
       if(j == matrix_columns(mtrx)-1)
        printf("\n");
    }
  }
}


void matrix_traverse(matrix_t* matrix, bool matrix_do(void* element,void* ctx),void* context){
  if(matrix == NULL){
    printf("matrix pointer is NULL");
    exit(-12);    
  }
  int rows = 0;
  int columns = 0;
  while(rows<matrix_rows(matrix)){
    while(columns<matrix_columns(matrix) && matrix_do(matrix_get(matrix,rows,columns),context)){
      columns++; 
    }
    if(columns == matrix_columns(matrix)){
      columns = 0;  
    }
    rows++;  
  }
}




