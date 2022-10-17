#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "Matrix.h"

matrix_t* matrix_int(int rows,int columns);
void matrix_delete(matrix_t** mtrx,void (*free_pointer)(void**));
void free_pointer(void** pointer);
void print_int(void* pointer);
int column_elements_addition(matrix_t* mtrx,int row,int columns);
int matrix_elements_addition(matrix_t* mtrx,int rows,int columns);

//ejemplo de aplicacion
int main(void){
  // creo una matrix de enteros
  matrix_t* matrix = matrix_int(5,5);
  //imprimo la matrix de enteros
  matrix_printf(matrix,print_int); 
  
  //calculo la suma de los elementos de la matriz de enteros
  int addition = matrix_elements_addition(matrix,matrix_rows(matrix),matrix_columns(matrix));
  printf("%i ",addition);
  
  //elimino la matriz con sus elementos
  matrix_delete(&matrix,free_pointer);
  return 0;    
}

//**********************ejemplos de funciones y procedimientos de uso del tda************************//

//crea una matriz de enteros
matrix_t* matrix_int(int rows,int columns){
  matrix_t* mtrx = matrix_new(rows,columns);
  srand(time(NULL));
  int* auxiliar = NULL;
  for(int i=0;i<matrix_rows(mtrx);i++){
    for(int j=0;j<matrix_columns(mtrx);j++){
      auxiliar = (int*)malloc(sizeof(int));
      *auxiliar = rand()%100;
      matrix_set(mtrx,i,j,auxiliar);         
    }  
  }
  return mtrx;  
}

//vacia la matriz y la elimina
void matrix_delete(matrix_t** mtrx,void (*free_pointer)(void**)){
  void* auxiliar = NULL;
  for(int i=0;i<matrix_rows(*mtrx);i++){
    for(int j=0;j<matrix_columns(*mtrx);j++){
      auxiliar = matrix_get(*mtrx,i,j);
      free_pointer(&auxiliar);        
    }  
  }
  matrix_free(mtrx);    
}


void free_pointer(void** pointer){
  free(*pointer);
  *pointer = NULL;    
}

void print_int(void* pointer){
  printf("%i ",*(int*)pointer);    
}


//suma de los elementos de una matriz  de forma recursiva
int matrix_elements_addition(matrix_t* mtrx,int rows,int columns){
  int returned = 0;
  if(rows>0){
    returned = column_elements_addition(mtrx,rows-1,columns) + matrix_elements_addition(mtrx,rows-1,columns);     
  }
  return returned;  
}

int column_elements_addition(matrix_t* mtrx,int row,int columns){
  int returned = 0;
  if(columns>0){
    returned = *(int*)matrix_get(mtrx,row,columns-1) + column_elements_addition(mtrx,row,columns-1);     
  }
  return returned;  
}
