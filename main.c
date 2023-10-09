#include <stdio.h>
#include <string.h>
#include "word.h"
#include "skipList.h"
/*
Issues da main:
O scanf("%s") é ruim para pegar termos com espaços, 
estou usando verbetes sem espaços nos meus testes,
mas deveremos decidir como tratar isso, podemos usar uma função tipo gets ou criar nossa própria,
ou pegar uma das dezenas que fizemos no lab de ICC1.
*/
void Insert(LISTA* lista){
  char title[40];
  char verbete[140];
  scanf(" %s", title);
  scanf(" %s", verbete);

  WORD* word = word_criar(title, verbete);
  if(lista_inserir(lista, word) == false)
    printf("OPERACAO INVALIDA\n");
}

void Alter(LISTA* lista){
  char title[40];
  char verbete[140];
  scanf(" %s", title);
  scanf(" %s", verbete);

  WORD* word = lista_remover(lista, title);
  if (word == NULL) printf("OPERACAO INVALIDA\n");
  else{
    word_set_verbete(word, verbete);
    lista_inserir(lista, word);
  }
}
void Remove(LISTA* lista){
  char title[40];
  scanf(" %s", title);

  WORD* word = lista_remover(lista, title);

  if (word == NULL) printf("OPERACAO INVALIDA\n");
  word_apagar(&word);
}

void Search(LISTA* lista){
  char title[40];
  scanf(" %s", title);

  WORD* word = lista_busca(lista, title);
  if (word == NULL) printf("OPERACAO INVALIDA\n");
  else word_imprimir_verbete(word);
}

void Print(LISTA* lista){
  char c;
  scanf(" %c", &c);
  if(lista_imprimir_de_caracter(lista, c) == false)
    printf("NAO HA PALAVRAS INICIADAS POR %c\n", c);
}


int main(void){
  char command[11];
  LISTA* dicionario = lista_criar(10);
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
