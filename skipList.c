#include "skipList.h"
#include "word.h"

// Cada célula tem uma palavra, um ponteiro para a célula debaixo (below) e um ponteiro para a célula a direita (next) 
typedef struct cell_{
  Word value;
  struct cell_* next;
  struct cell_* below;
}cellObj;
typedef cellObj* Cell;


// A Skip list tem um vetor com todas as cabeças das listas ligadas, a profundidade da Skip list (numero de listas ligadas) (depth) e o numero de diferentes elementos inseridos (length)
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


// Essa função recebe um vetor de células e insere uma nova palavra à frente delas, de baixo pra cima, 50% das vezes, caso não seja inserida o loop é quebrado e não será inserido nas células de cima
void insertInCells(Word word, Cell* vector, int depth){
  Cell inputCell = createCell(word);

  inputCell->next = vector[0]->next; // Primeiro inserimos na posição zero sem depender de alguma probabilidade
  vector[0]->next = inputCell;

  for(int i = 1; i < depth; i++){ // Depois inserimos nas outras posições dependendo de uma probabilidade
    if(rand() % 2 == 0) break;

    Cell inputCell = createCell(word);

    inputCell->next = vector[i]->next;
    vector[i]->next = inputCell;

    inputCell->below = vector[i-1]->next;
  }
}

// Essa funçaõ recebe uma palavra e a insere na skip list, retornando true se a inserção deu certo, ou false se qualquer fator a impediu de ser realizada
bool lista_inserir(LISTA *lista, WORD *word){
  if (lista == NULL || word == NULL) return false; //checagens em relação aos parâmetros
  if(lista_cheia(lista)) return false;
  
  
  Cell currentCell = lista->vector[lista->depth-1]; // Esse será o ponteiro que irá percorrar a lista
  Cell nextCell = NULL; // Esse ponteiro representa o next da currentCell, será usado para analisar se há uma célula após a currentCell e se sim, se o title dela é maior ou igual ao da palavra que desejamos inserir

  Cell vector[lista->depth]; // Esse vetor contém todas as células que estão anteriores a posição de inserção, uma célula por nível
  int vectorIndex = lista->depth-1; // Esse número é a profundidade da célula atual (começa em depth-1 pois percorremos a lista de cima para baixo)
  
  while(1){ // Dentro desse while ocorre a busca pelo elemento anterior a posição que desejamos inserir
    nextCell = currentCell->next;
    
    if (nextCell == NULL && currentCell->below == NULL) { // Checamos se a célula atual é a ultima do andar 0, se sim quebramos a busca pois queremos inserir no fim da lista
      vector[vectorIndex] = currentCell;
      vectorIndex--;
      break;
    }
    
    else if (nextCell == NULL) { // Checamos se a célula atual é a última da lista ligada, se for desceremos para o andar de baixo
      vector[vectorIndex] = currentCell;
      currentCell = currentCell->below;
      vectorIndex--;
      continue;
    }
    
    else if(word_compare(nextCell->value, word) >= 0){ // Comparamos se a célula a frente da atual possui um title "maior" que o title da palavra a ser inserida
      if(vectorIndex == 0){ // Se estivermos no andar 0, queremos parar a busca pois o vector já estará completamente preenchido com a célula anterior a posição de inserção de todos os andares
        vector[vectorIndex] = currentCell;
        vectorIndex--;
        break;
      }

      vector[vectorIndex] = currentCell; // Caso não estivermos, queremos descer para o próximo andar
      currentCell = currentCell->below;
      vectorIndex--;
      continue;
    }
    currentCell = currentCell->next; // Passamos para a célula da frente caso nenhuma checagem seja verdadeira
  } // No fim desse loop, currentCell está na célula anterior a posição de inserção e o vector está completamente preenchido

  if(currentCell->next != NULL) // Se currentCell não for a última célula, e a célula a sua frente tiver mesmo título da palavra que queremos inserir, estamos inserindo a mesma palavra duas vezes, por isso retornamos false
    if(word_compare(word, nextCell->value) == 0)
      return false;

  insertInCells(word, vector, lista->depth); // Inserimos a palavra na frente das células de vector, de baixo pra cima, dependendo de uma probabilidade
  lista->length+=1; 
  return true;
}

// Essa função recebe um vetor de células e remove a célula posterior caso exista
void removeInCells(Cell* vector, int depth, Word word){
  for(int i = 0; i < depth; i++){
    if(vector[i]->next != NULL && vector[i]->next->value !=NULL) // Se a célula analizada não ser a última da lista ligada
      if(word_compare(vector[i]->next->value, word) == 0){ // Se o título da palavra for igual ao da próxima célula, a próxima célula será apagada
        Cell removedCell = vector[i]->next;
        vector[i]->next = removedCell->next;
        
        if(i != 0){ // Exceção da célula do andar 0, que será ainda utilizada
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
  Word word = word_criar(title, tempVerbete); // é criada uma palavra temporária para comparação de seu título com o título de palavras da lista

  Cell currentCell = lista->vector[lista->depth-1];
  Cell nextCell = NULL;

  Cell vector[lista->depth]; // vector terá mesma função que o vector da lista_inserir, será as células uma posição anterior onde a palavra seria inserida
  int vectorIndex = lista->depth-1;
  
  while(1){ // A busca funciona da mesma forma que a busca da lista_inserir
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

  Cell returnalCell = currentCell->next; // returnalCell é a célula posterior a currentCell, como currentCell representa a célula anterior a posição que a palavra seria inserida, se a palavra existir no dicionário ela estará em returnalCell
  if(returnalCell == NULL) { // Se a currentCell for a última célula do andar 0, significa que a palavra a ser removida não existe no dicionário, portanto retorna-se NULL
    word_apagar(&word);
    return NULL;
  }
  if(word_compare(returnalCell->value, word) != 0) { // Se a palavra que está após a currentCell não tiver mesmo título da palavra a ser removida, significa que esta palavra não está no dicionário e portanto retorna-se NULL
    word_apagar(&word);
    return NULL;
  }
  
  removeInCells(vector, lista->depth, word); // Remove-se do vector todas as células que tiverem mesmo title da que desejamos remover
  Word returnal = returnalCell->value;

  free(returnalCell);
  word_apagar(&word);
  
  lista->length-=1;
  return returnal;
}

// Essa função recebe um titulo, procura a palavra com o titulo dentro da skip list e o retorna
Word lista_busca(LISTA *lista, char* title){ // Segue a mesma lógica que a lista_remover, a única diferença sendo que a palavra não é apagada da lista, apenas sendo retornada caso exista
  if (lista == NULL) return NULL;
  else if(lista_cheia(lista)) return NULL;
   
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
    
    else if(strcmp(word_get_title(nextCell->value), title)>= 0){
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
    return NULL;
  }
  else if(strcmp(word_get_title(nextCell->value), title)!= 0){
    return NULL;
  }
  
  
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
  for(int i = lista->depth-1; i >=0; i--){
    Cell iterCell = lista->vector[i]->next;
    for(; iterCell!=NULL; iterCell = iterCell->next)
      word_imprimir(iterCell->value);
    
    printf("\n");
  }
}

// Essa função imprime todos os elementos da última lista que comeca com um caracter especifico
bool lista_imprimir_de_caracter(LISTA *lista, char c){ // Utiliza da mesma busca da lista_inserir para achar a posição anterior onde a palavra contendo apenas o caracter seria inserido
  if (lista == NULL) return false;
  else if(lista_cheia(lista)) return false;
 
  char title[2]; // title é usado apenas para transformar o caracter em uma string
  title[0] = c;
  title[1] = '\0';

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
    
    else if(strcmp(word_get_title(nextCell->value), title)>= 0){
      if(vectorIndex == 0){
        vectorIndex--;
        break;
      }

      currentCell = currentCell->below;
      vectorIndex--;
      continue;
    }
    currentCell = currentCell->next;
  } // No fim da busca, currentCell está uma posição antes da primeira palavra que começa com o caracter

  if(currentCell->next == NULL) return false; // Se não houver célula após currentCell, não existe palavra começando com caracter, assim retorna-se false
  if (word_get_title(currentCell->next->value)[0] != c) // Se não houver célula após currentCell que começe com caracter, não existe palavra começando com caracter, assim retorna-se false
    return false;
  
  while(currentCell->next!=NULL){ // Este loop imprime todas as palavras que começam com o caracter, até que acabe as palavras ou ache uma palavra que não começa com caracter
    currentCell = currentCell->next;
    Word wordToPrint = currentCell->value;
    
    if (word_get_title(wordToPrint)[0] == c)
      word_imprimir(wordToPrint);
    else break; 
  }
  
  return true;
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

