#include <stdlib.h>
#include <stdio.h>
#include "item.h"

/*
Este � o tad item que ser� usado dentro do tad �rvore AVL
*/

struct item_{ 
  int chave;
};

ITEM *item_criar (int chave){ // Esta fun��o recebe um inteiro e retorna um endere�o de um item com este inteiro
  ITEM *item;
  
  item = (ITEM *) malloc(sizeof(ITEM));
  
  if (item != NULL){
     item->chave = chave;
     return(item);
  }
  return(NULL);
}

bool item_apagar(ITEM **item){ // Esta fun��o recebe um endere�o de um ponteiro para item, o apaga, e muda ele para NULL, retornando falso se ele j� for NULL
  if (*item != NULL){
    free (*item);
    *item = NULL;
    return(true);
  }
  return(false);
}

int item_get_chave(ITEM *item){ // Esta fun��o recebe um endere�o de um item e retorna o inteiro nele armazenado
    if (item != NULL)
      return(item->chave);
    exit(1);
}


bool item_set_chave(ITEM *item, int chave){ // Esta fun��o recebe um endere�o de um item e um inteiro, e coloca o inteiro dentro do item. Retorna falso se o item for NULL
  if (item != NULL){
    item->chave = chave;
    return (true);
  }
  return (false);
}

void item_imprimir(ITEM *item){ // Esta fun��o imprime o valor de um item
     if (item != NULL)
        printf("%d\n", item->chave);
}
