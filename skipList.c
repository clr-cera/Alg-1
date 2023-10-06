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

// This functions return listas length property
int lista_tamanho(SkipList lista){
  return lista->length;
}

// This function sees if there is any cell in the bottom linked list
bool lista_vazia(SkipList lista){
  if(lista->vector[0]->next == NULL) return true;
  else return false;
}

// This function tries to create a new cell, if it is impossible, then there is no ram memory
bool lista_cheia(SkipList lista){
  Cell test = createCell(NULL);
  bool returnal;
  
  if (test == NULL) returnal = true;
  else returnal = false;

  free(test);
  return returnal;
}

// This function prints all elements from bottom linked list
void lista_imprimir(SkipList lista){
  Cell iterCell = lista->vector[0]->next;
  for(; iterCell!=NULL; iterCell = iterCell->next)
    printf("Palavra: %s Verbete: %s\n", word_get_title(iterCell->value), word_get_verbete(iterCell->value));
}

// This function frees a linked list
void linkedListApagar(Cell head){
  Cell lastCell = head;
  Cell currentCell = head;

  while(currentCell != NULL){
    lastCell = currentCell;
    currentCell = currentCell->next ;
    free(lastCell);
  }
}

// This function frees a Skip List
void lista_apagar(SkipList* lista){
  for(int i = 0; i < (*lista)->length; i++)
    linkedListApagar((*lista)->vector[i]);
  
  free(*lista);
  *lista = NULL;
}

