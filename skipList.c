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
  result->next = NULL;
  result->below = NULL;
  
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

  // Set Random Seed
  srand(time(0));

  return result;
}


// Essa função recebe um vetor de células e insere uma nova palavra à frente delas
void insertInCells(Word word, Cell* vector, int depth){
  Cell inputCell = createCell(word);

  inputCell->next = vector[0]->next;
  vector[0]->next = inputCell;

  for(int i = 1; i < depth; i++){
    if(rand() % 2 == 0) break;

    Cell inputCell = createCell(word);

    inputCell->next = vector[i]->next;
    vector[i]->next = inputCell;

    inputCell->below = vector[i-1]->next;
  }
}


// Essa funçaõ recebe uma palavra e a insere na skip list
bool lista_inserir(LISTA *lista, WORD *word){
  if (lista == NULL || word == NULL) return false;
  if(lista_cheia(lista)) return false;
  
  
  Cell currentCell = lista->vector[lista->depth-1];
  Cell nextCell = NULL;

  Cell vector[lista->depth];
  int vectorIndex = lista->depth-1;
  
  while(1){
    nextCell = currentCell->next;
    
    if (nextCell == NULL && currentCell->below == NULL) {
      vector[vectorIndex] = currentCell;
      vectorIndex--;
      break;
    }
    
    else if (nextCell == NULL) {
      vector[vectorIndex] = currentCell;
      currentCell = currentCell->below;
      vectorIndex--;
      continue;
    }
    
    else if(word_compare(nextCell->value, word) > 0){
      if(vectorIndex == 0){
        vector[vectorIndex] = currentCell;
        vectorIndex--;
        break;
      }

      vector[vectorIndex] = currentCell;
      currentCell = currentCell->below;
      vectorIndex--;
      continue;
    }
    currentCell = currentCell->next;
  }

  
  insertInCells(word, vector, lista->depth);
  lista->length+=1;
  return true;
}

// Essa função recebe um vetor de células e remove a célula posterior caso exista
void removeInCells(Cell* vector, int depth, Word word){
  for(int i = 0; i < depth; i++){
    if(vector[i]->next != NULL)
      if(word_compare(vector[i]->next->value, word) == 0){
        Cell removedCell = vector[i]->next;
        vector[i]->next = removedCell->next;
        
        if(i != 0){
          word_apagar(&(removedCell->value));
          free(removedCell);
        }
      }
  }
}

// Essa função remove uma palavra da skip list
Word lista_remover(LISTA *lista, char* title){
  if (lista == NULL) return NULL;
  else if(lista_cheia(lista)) return NULL;
  
  char tempVerbete[2] = "t";
  Word word = word_criar(title, tempVerbete);  

  Cell currentCell = lista->vector[lista->depth-1];
  Cell nextCell = NULL;

  Cell vector[lista->depth];
  int vectorIndex = lista->depth-1;
  
  while(1){
    nextCell = currentCell->next;
    
    if (nextCell == NULL && currentCell->below == NULL) {
      vector[vectorIndex] = currentCell;
      vectorIndex--;
      break;
    }
    
    else if (nextCell == NULL) {
      vector[vectorIndex] = currentCell;
      currentCell = currentCell->below;
      vectorIndex--;
      continue;
    }
    
    else if(word_compare(nextCell->value, word) >= 0){
      if(vectorIndex == 0){
        vector[vectorIndex] = currentCell;
        vectorIndex--;
        break;
      }

      vector[vectorIndex] = currentCell;
      currentCell = currentCell->below;
      vectorIndex--;
      continue;
    }
    currentCell = currentCell->next;
  }

  Cell returnalCell = currentCell->next;
  if(returnalCell == NULL) {
    word_apagar(&word);
    return NULL;
  }
  if(word_compare(returnalCell->value, word) != 0) {
    word_apagar(&word);
    return NULL;
  }
  
  removeInCells(vector, lista->depth, word);
  Word returnal = returnalCell->value;

  free(returnalCell);
  word_apagar(&word);
  
  return returnalCell->value;
}

// Essa função recebe um titulo, procura a palavra com o titulo dentro da skip list e o retorna
Word lista_busca(LISTA *lista, char* title){
  if (lista == NULL) return NULL;
  else if(lista_cheia(lista)) return NULL;
  
  char tempVerbete[2] = "t";
  Word word = word_criar(title, tempVerbete); 
  
  Cell currentCell = lista->vector[lista->depth-1];
  Cell nextCell = NULL;

  int vectorIndex = lista->depth-1;
  
  while(1){
    nextCell = currentCell->next;
    
    if (nextCell == NULL && currentCell->below == NULL) {
      vectorIndex--;
      break;
    }
    
    else if (nextCell == NULL) {
      currentCell = currentCell->below;
      vectorIndex--;
      continue;
    }
    
    else if(word_compare(nextCell->value, word) >= 0){
      if(vectorIndex == 0){
        vectorIndex--;
        break;
      }

      currentCell = currentCell->below;
      vectorIndex--;
      continue;
    }
    currentCell = currentCell->next;
  }

  Cell returnalCell = currentCell->next;

  if(returnalCell == NULL) {
    word_apagar(&word);
    return NULL;
  }
  if(word_compare(returnalCell->value, word) != 0) {
    word_apagar(&word);
    return NULL;
  }
  
  word_apagar(&word);
  
  return returnalCell->value;
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
    word_imprimir(iterCell->value);
}

void lista_imprimir_de_caracter(LISTA *lista, char c){
  if (lista == NULL) return;
  else if(lista_cheia(lista)) return;
  
  char title[2];
  title[0] = c;
  char tempVerbete[2] = "t";

  Word word = word_criar(title, tempVerbete); 
  
  Cell currentCell = lista->vector[lista->depth-1];
  Cell nextCell = NULL;

  int vectorIndex = lista->depth-1;
  
  while(1){
    nextCell = currentCell->next;
    
    if (nextCell == NULL && currentCell->below == NULL) {
      vectorIndex--;
      break;
    }
    
    else if (nextCell == NULL) {
      currentCell = currentCell->below;
      vectorIndex--;
      continue;
    }
    
    else if(word_compare(nextCell->value, word) >= 0){
      if(vectorIndex == 0){
        vectorIndex--;
        break;
      }

      currentCell = currentCell->below;
      vectorIndex--;
      continue;
    }
    currentCell = currentCell->next;
  }

  while(currentCell->next!=NULL){
    currentCell = currentCell->next;
    Word wordToPrint = currentCell->value;
    if (word_get_title(wordToPrint)[0] == c)
      word_imprimir(wordToPrint);
    else break; 
  }
  

  word_apagar(&word); 
  return;
}

// Essa função apaga uma lista ligada
void linkedListApagar(Cell head, int index){
  Cell lastCell = head;
  Cell currentCell = head;

  while(currentCell != NULL){
    lastCell = currentCell;
    currentCell = currentCell->next;

    if (lastCell->value != NULL && index == 0)
      word_apagar(&(lastCell->value));
    
    free(lastCell);
  }
}

// Essa função apaga uma Skip List
void lista_apagar(SkipList* lista){
  for(int i = 0; i < (*lista)->depth; i++)
    linkedListApagar((*lista)->vector[i], i);
 
  free((*lista)->vector);
  free(*lista);
  *lista = NULL;
}

/*
int main(void){
  int depth, n;
  scanf("%d %d", &depth, &n);
  SkipList lista = lista_criar(depth);
  
  for(int i = 0; i < n; i++){
    char title[40];
    char verbete[140];
    scanf(" %s", title);
    scanf(" %s", verbete);
    
    Word word = word_criar(title, verbete);

    lista_inserir(lista, word);
  }

  printf("Will print all c\n");
  lista_imprimir_de_caracter(lista, 'c');

  lista_apagar(&lista);
  return 0;
}
*/
