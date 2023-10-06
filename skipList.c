#include "skipList.h"
#include "word.h"

// Cada célula tem uma palavra, um ponteiro para a célula debaixo e um ponteiro para a célula a direita 
typedef struct cell_{
  Word value;
  struct cell_* next;
  struct cell_* below;
}cellObj;
typedef cellObj* Cell;


// A Skip list tem um vetor com todas as cabeças das listas ligadas, a profundidade da Skip list (numero de listas) e o numero de diferentes elementos
typedef struct skipList_{
  Cell* vector;
  int depth;
  int length;
}skipListObj;
typedef skipListObj* SkipList;


// Essa funcão recebe uma palavra e retorna uma célula contendo essa palavra
Cell createCell(Word input){
  Cell result = (Cell) malloc(sizeof(cellObj));
  
  result->value = input;
  
  return result;
}

// Essa função recebe uma profudidade e retorna uma skip list com essa profundidade
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

// Essa função retorna a propriedade length da lista
int lista_tamanho(SkipList lista){
  return lista->length;
}

// Essa função retorna true se não houver células na última lista ligada
bool lista_vazia(SkipList lista){
  if(lista->vector[0]->next == NULL) return true;
  else return false;
}

// Essa função tenta criar uma célula, se não houver espaço, ela retorna true
bool lista_cheia(SkipList lista){
  Cell test = createCell(NULL);
  
  if (test == NULL) return true;

  free(test);
  return false;
}

// Essa função imprime todos os elementos da última lista
void lista_imprimir(SkipList lista){
  Cell iterCell = lista->vector[0]->next;
  for(; iterCell!=NULL; iterCell = iterCell->next)
    printf("Palavra: %s Verbete: %s\n", word_get_title(iterCell->value), word_get_verbete(iterCell->value));
}

// Essa função apaga uma lista ligada
void linkedListApagar(Cell head){
  Cell lastCell = head;
  Cell currentCell = head;

  while(currentCell != NULL){
    lastCell = currentCell;
    currentCell = currentCell->next ;
    free(lastCell);
  }
}

// Essa função apaga uma Skip List
void lista_apagar(SkipList* lista){
  for(int i = 0; i < (*lista)->length; i++)
    linkedListApagar((*lista)->vector[i]);
  
  free(*lista);
  *lista = NULL;
}

