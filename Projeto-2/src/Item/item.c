#include <stdlib.h>
#include <stdio.h>
#include "item.h"

/*
Este é o tad item que será usado dentro do tad árvore AVL
*/

struct item_{ 
  int chave;
};

ITEM *item_criar (int chave){ // Esta função recebe um inteiro e retorna um endereço de um item com este inteiro
  ITEM *item;
  
  item = (ITEM *) malloc(sizeof(ITEM));
  
  if (item != NULL){
     item->chave = chave;
     return(item);
  }
  return(NULL);
}

bool item_apagar(ITEM **item){ // Esta função recebe um endereço de um ponteiro para item, o apaga, e muda ele para NULL, retornando falso se ele já for NULL
  if (*item != NULL){
    free (*item);
    *item = NULL;
    return(true);
  }
  return(false);
}

int item_get_chave(ITEM *item){ // Esta função recebe um endereço de um item e retorna o inteiro nele armazenado
    if (item != NULL)
      return(item->chave);
    exit(1);
}


bool item_set_chave(ITEM *item, int chave){ // Esta função recebe um endereço de um item e um inteiro, e coloca o inteiro dentro do item. Retorna falso se o item for NULL
  if (item != NULL){
    item->chave = chave;
    return (true);
  }
  return (false);
}

void item_imprimir(ITEM *item){ // Esta função imprime o valor de um item
     if (item != NULL)
        printf("%d\n", item->chave);
}
