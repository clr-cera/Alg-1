#include <stdio.h>
#include <string.h>
#include "word.h"
#include "skipList.h"

void Insert(LISTA* lista){
  char title[40];
  char verbete[140];
  scanf(" %s", title);
  scanf(" %s", verbete);

  WORD* word = word_criar(title, verbete);
  lista_inserir(lista, word);
}
void Alter(LISTA* lista){
  char title[40];
  char verbete[140];
  scanf(" %s", title);
  scanf(" %s", verbete);

  WORD* word = lista_remover(lista, title);
  word_set_verbete(word, verbete);
  lista_inserir(lista, word);
}
void Remove(LISTA* lista){
  char title[40];
  scanf(" %s", title);

  WORD* word = lista_remover(lista, title);
  word_apagar(&word);
}
void Search(LISTA* lista){
  char title[40];
  scanf(" %s", title);

  WORD* word = lista_busca(lista, title)
  word_imprimir_verbete(word);
}
void Print(LISTA* lista){
  lista_imprimir(lista);
}


int main(void){
  char command[11];
  LISTA* dicionario = lista_criar();
  while(1){
    scanf(" %s", command);
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
}
