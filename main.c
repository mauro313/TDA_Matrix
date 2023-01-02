#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include "Matrix.h"

matrix_t* matrix_int(int rows,int columns);
void matrix_delete(matrix_t** mtrx,void (*free_pointer)(void**));
void free_pointer(void** pointer);
void print_int(void* pointer);
int compare(void* element1,void* element2);
int row_elements_addition(matrix_t* mtrx,int row,int columns);
int matrix_elements_addition(matrix_t* mtrx,int rows,int columns);
bool matrix_addition(void* element,void* context);
void* row_maxElement(matrix_t* matrix,int row,int columns,int(*compare)(void*,void*));
void* matrix_maxElement(matrix_t* matrix,int rows,int columns,int(*compare)(void*,void*));


int main(void){
  // creo una matrix de enteros
  matrix_t* matrix = matrix_int(5,5);
 
  //imprimo la matrix de enteros
  matrix_printf(matrix,print_int); 
  
  //calculo la suma de los elementos de la matriz de enteros con matrix traverse
  int addition = 0;
  matrix_traverse(matrix,matrix_addition,&addition);
  printf("\naddition of all elements: %d \n",addition);

  //suma de todos los elementos de forma recursiva
  printf("addition of all elements: %d \n",matrix_elements_addition(matrix,matrix_rows(matrix),matrix_columns(matrix)));

  //maximo elemento de la matrix
  printf("max element of matrix: %d \n",*(int*)matrix_maxElement(matrix,matrix_rows(matrix),matrix_columns(matrix),compare));

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

//procedimientos auxiliares y funcion de comparacion de genericos
void free_pointer(void** pointer){
  free(*pointer);
  *pointer = NULL;    
}

void print_int(void* pointer){
  printf("%i ",*(int*)pointer);  
}

int compare(void* element1,void* element2){
  return (*(int*)element1)-(*(int*)element2);     
}
///////////////////////////////

//suma de los elementos de una matriz de forma recursiva
int matrix_elements_addition(matrix_t* mtrx,int rows,int columns){
  int returned = 0;
  if(rows>0){
    returned = row_elements_addition(mtrx,rows-1,columns) + matrix_elements_addition(mtrx,rows-1,columns);     
  }
  return returned;  
}

// suma de los elementos de una fila de la matriz
int row_elements_addition(matrix_t* mtrx,int row,int columns){
  int returned = 0;
  if(columns>0){
    returned = *(int*)matrix_get(mtrx,row,columns-1) + row_elements_addition(mtrx,row,columns-1);     
  }
  return returned;  
}

// funcion prueba para matrix_traverse
bool matrix_addition(void* element,void* context){
  bool returned = false;
  if(element != NULL){
    *(int*)context += *(int*)element;              
    returned = true;
  }
  return returned;      
}

// maximo de una fila de la matriz 
void* row_maxElement(matrix_t* matrix,int row,int columns,int(*compare)(void*,void*)){
  void* returned = NULL;
  if(matrix == NULL){
    printf("matrix pointer is NULL");
    return NULL;  
  }
  if(columns>1){
    void* auxiliar = matrix_get(matrix,row-1,columns-1);
    returned = row_maxElement(matrix,row,columns-1,compare);
    if(compare(auxiliar,returned)>=0){
      returned = auxiliar;     
    }
  }
  if(columns == 1){
    returned = matrix_get(matrix,row-1,columns-1); 
  } 
  return returned;
}

// maximo de la matriz de forma recursiva usando row_maxElement
void* matrix_maxElement(matrix_t* matrix,int rows,int columns,int(*compare)(void*,void*)){
  if(matrix == NULL){
    printf("matrix pointer is NULL");
    return NULL;  
  }
  void* returned = NULL;
  if(rows>1){
    void* auxiliar = row_maxElement(matrix,rows,columns,compare);
    returned = matrix_maxElement(matrix,rows-1,columns,compare);
    if(compare(auxiliar,returned)>=0){
      returned = auxiliar;     
    }   
  }
  if(rows == 1){
    returned = row_maxElement(matrix,rows,columns,compare);   
  }
  return returned;   
}









