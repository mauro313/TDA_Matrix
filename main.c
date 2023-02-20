#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include "Matrix.h"

matrix_t* matrix_int(int rows,int columns);
void matrix_erase(matrix_t** mtrx,void (*free_pointer)(void**));
void free_pointer(void** pointer);
void print_int(void* pointer);
int compare(void* element1,void* element2);
int row_elements_addition(matrix_t* mtrx,int row,int columns);
int matrix_elements_addition(matrix_t* mtrx,int rows,int columns);
bool matrix_addition(void* element,void* context);
void* row_maxElement(matrix_t* matrix,int row,int columns,int(*compare)(void*,void*));
void* matrix_maxElement(matrix_t* matrix,int rows,int columns,int(*compare)(void*,void*));


int main(void){
  // creation of a int matrix.
  matrix_t* matrix = matrix_int(5,5);

  //print the matrix.
  matrix_printf(matrix,print_int); 

  //calculate the addition of all the elements of the matrix.
  int addition = 0;
  matrix_traverse(matrix,matrix_addition,&addition);
  printf("\naddition of all elements: %d \n",addition);

  //addition of all the elements in a recursive form.
  printf("addition of all elements: %d \n",matrix_elements_addition(matrix,matrix_rows(matrix),matrix_columns(matrix)));

  //calculate the max element of the matrix.
  printf("max element of matrix: %d \n",*(int*)matrix_maxElement(matrix,matrix_rows(matrix),matrix_columns(matrix),compare));

  //erase the matrix with all the elements.
  matrix_erase(&matrix,free_pointer);

  return 0;    
}

//**********************EXAMPLES OF USE OF TDA.************************//

/**
 * @brief create a int matrix.
 * 
 * @param rows 
 * @param columns 
 * @return matrix_t* 
 */
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

/**
 * @brief delete the matrix with all his elements and free the used memory.
 * 
 * @param mtrx 
 * @param free_pointer 
 */
void matrix_erase(matrix_t** mtrx,void (*free_pointer)(void**)){
  void* auxiliar = NULL;
  for(int i=0;i<matrix_rows(*mtrx);i++){
    for(int j=0;j<matrix_columns(*mtrx);j++){
      auxiliar = matrix_get(*mtrx,i,j);
      free_pointer(&auxiliar);        
    }  
  }
  matrix_free(mtrx);    
}

/**
 * @brief auxiliar procedure to free the memory of a int pointer.
 * 
 * @param pointer 
 */
void free_pointer(void** pointer){
  free(*pointer);
  *pointer = NULL;    
}

/**
 * @brief auxiliar procedure to free a int pointer.
 * 
 * @param pointer 
 */
void print_int(void* pointer){
  printf("%i ",*(int*)pointer);  
}

/**
 * @brief auxiliar compare function.
 * 
 * @param element1 
 * @param element2 
 * @return int 
 */
int compare(void* element1,void* element2){
  return (*(int*)element1)-(*(int*)element2);     
}

/**
 * @brief calculate the addition of all the elements of a int matrix.
 * 
 * @param mtrx 
 * @param rows 
 * @param columns 
 * @return int 
 */
int matrix_elements_addition(matrix_t* mtrx,int rows,int columns){
  int returned = 0;
  if(rows>0){
    returned = row_elements_addition(mtrx,rows-1,columns) + matrix_elements_addition(mtrx,rows-1,columns);     
  }
  return returned;  
}

/**
 * @brief calculate the addition of all the elements of the specified row.
 * 
 * @param mtrx 
 * @param row 
 * @param columns 
 * @return int 
 */
int row_elements_addition(matrix_t* mtrx,int row,int columns){
  int returned = 0;
  if(columns>0){
    returned = *(int*)matrix_get(mtrx,row,columns-1) + row_elements_addition(mtrx,row,columns-1);     
  }
  return returned;  
}

/**
 * @brief function to test matrix addition.
 * 
 * @param element 
 * @param context 
 * @return true 
 * @return false 
 */
bool matrix_addition(void* element,void* context){
  bool returned = false;
  if(element != NULL){
    *(int*)context += *(int*)element;              
    returned = true;
  }
  return returned;      
}

/**
 * @brief get the max element of the specified row.
 * 
 * @param matrix 
 * @param row 
 * @param columns 
 * @param compare 
 * @return void* 
 */
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

/**
 * @brief get the max element of the matrix.Use of row_maxElement.
 * 
 * @param matrix 
 * @param rows 
 * @param columns 
 * @param compare 
 * @return void* 
 */
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









