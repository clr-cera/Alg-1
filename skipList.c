#include "skipList.h"
#include "word.h"

// Each cell has a word, a pointer to the cell below and a pointer to the cell on right
typedef struct cell_{
  Word value;
  struct cell_* next;
  struct cell_* below;
}cellObj;
typedef cellObj* Cell;

// The SkipList has a vector with all heads of linked lists, the depth of the linked list and the length of the bottom linked list
typedef struct skipList_{
  Cell* vector;
  int depth;
  int length;
}skipListObj;
typedef skipListObj* SkipList;

// This funcion takes a word and returns a cell with this word
Cell createCell(Word input){
  Cell result = (Cell) malloc(sizeof(cellObj));
  
  result->value = input;
  
  return result;
}

// This function takes depth and returns a SkipList with that depth
SkipList lista_criar(int depth){
  SkipList result = (SkipList) malloc(sizeof(skipListObj));
  
  result->length = 0;
  result->depth = depth;
  result->vector = (Cell*) malloc(sizeof(Cell) * depth);

  for(int i = 0; i < depth; i++){
    result->vector[i] = createCell(NULL);
    result->vector[i]->next = NULL;

    if (i > 0)
      result->vector[i]->below = result->vector[i-1];
    else result->vector[i]->below = NULL;
  }

  return result;
}

