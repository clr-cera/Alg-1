#include <stdio.h>
#include <string.h>
#include "word.h"
#include "skipList.h"

char* readString();

void Insert(LISTA* lista){
  char title[50];
  char* verbete;
  scanf(" %s", title);
  verbete = readString();

  WORD* word = word_criar(title, verbete);
  if(lista_inserir(lista, word) == false)
    printf("OPERACAO INVALIDA\n");
}

void Alter(LISTA* lista){
  char title[50];
  scanf(" %s", title);

  WORD* word = lista_remover(lista, title);

  if (word == NULL) {printf("OPERACAO INVALIDA\n"); return;}
  word_apagar(&word);

  char* verbete;
  verbete = readString();

  word = word_criar(title, verbete);
  if(lista_inserir(lista, word) == false)
    printf("OPERACAO INVALIDA\n");
}
void Remove(LISTA* lista){
  char title[50];
  scanf(" %s", title);

  WORD* word = lista_remover(lista, title);

  if (word == NULL) printf("OPERACAO INVALIDA\n");
  word_apagar(&word);
}

void Search(LISTA* lista){
  char title[50];
  scanf(" %s", title);

  WORD* word = lista_busca(lista, title);
  if (word == NULL) printf("OPERACAO INVALIDA\n");
  else word_imprimir(word);
}

void Print(LISTA* lista){
  char c;
  scanf(" %c", &c);

  if(lista_imprimir_de_caracter(lista, c) == false)
    printf("NAO HA PALAVRAS INICIADAS POR %c\n", c);
}


int main(void){
  char command[12];
  LISTA* dicionario = lista_criar(100);
  
  while(1){
    if((scanf(" %s", command)) == EOF) break;
    
    if     (strcmp(command, "insercao") == 0)
      Insert(dicionario);

    else if(strcmp(command, "alteracao") == 0)
      Alter(dicionario);

    else if(strcmp(command, "remocao") == 0)
      Remove(dicionario);

    else if(strcmp(command, "busca") == 0)
      Search(dicionario);

    else if(strcmp(command, "impressao") == 0)
      Print(dicionario);
  }
  
  lista_apagar(&dicionario);
  return 0;
}

char* readString(){
  char input;
  int length = 0;
  char* string;
  string = (char *) malloc(20 * sizeof(char));
  int firstCharFlag = 1;

  while (1){
    input = getchar();
    if (input == ' ' && firstCharFlag == 1){
      continue;
    }
    firstCharFlag = 0;

    if (input == '\n' || input == 13)
      break;
    
    string[length] = input;
    length++;

    if (length % 20 == 0)
      string = (char *) realloc(string, (length + 20) * sizeof(char));

  }

  string[length] = '\0';
  //  length++;

  //printf("Recebi a string!\n"); //DEBUG
  return(string);
}
