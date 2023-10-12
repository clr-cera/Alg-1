#include <stdio.h>
#include <string.h>
#include "word.h"
#include "skipList.h"

char* readString();

//Lê os dados necessários e cria e insere uma palavra na lista
void Insert(LISTA* lista){
  char title[51];
  char* verbete;
  scanf(" %s", title);
  verbete = readString();

  WORD* word = word_criar(title, verbete);
  if(lista_inserir(lista, word) == false){
    printf("OPERACAO INVALIDA\n");
    word_apagar(&word);
  }
  
  free(verbete);
}

//Lê os dados necessários e altera o verbete de uma palavra da lista
void Alter(LISTA* lista){
  char title[51];
  scanf(" %s", title);

  WORD* word = lista_busca(lista, title);
  
  char* verbete;
  verbete = readString();
  
  if (word == NULL) {printf("OPERACAO INVALIDA\n"); free(verbete); return;}

  word_set_verbete(word, verbete);
  free(verbete);
}

//Lê os dados necessários e remove uma palavra da lista
void Remove(LISTA* lista){
  char title[51];
  scanf(" %s", title);

  WORD* word = lista_remover(lista, title);

  if (word == NULL) {printf("OPERACAO INVALIDA\n"); return;}
  word_apagar(&word);
}

//Lê os dados necessários e imprime o verbete de uma palavra já presente na lista
void Search(LISTA* lista){
  char title[51];
  scanf(" %s", title);

  WORD* word = lista_busca(lista, title);
  if (word == NULL) printf("OPERACAO INVALIDA\n");
  else word_imprimir(word);
}

//Lê um caracter e imprime todas as palavras da lista que iniciam com tal caracter
void Print(LISTA* lista){
  char c;
  scanf(" %c", &c);

  if(lista_imprimir_de_caracter(lista, c) == false)
    printf("NAO HA PALAVRAS INICIADAS POR %c\n", c);
}

//Seleciona qual das funções acima serão executadas
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

//Função que lê uma string até encontrar o \n ou EOF, utilizada para receber os verbetes que contém o espaço
char* readString(){
  char input;
  int length = 0;
  char* string;
  string = (char *) malloc(20 * sizeof(char));
  int firstCharFlag = 1;

  while (1){
    if((input = getchar()) == EOF) break;
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
  return(string);
}
