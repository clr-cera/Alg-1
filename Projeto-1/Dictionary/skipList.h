#ifndef LISTA_H
	#define LISTA_H
/*
Criei uma base baseada no meu TAD de lista encadeada ordenada, 
mas provavelmente vai precisar de muitas mudanças para se adaptar a skipList.
*/
	#include "word.h"
	#include <stdbool.h>
  #include <stdlib.h>
  #include <time.h>

  typedef struct cell_* Cell;
  typedef struct skipList_* SkipList;
  typedef struct skipList_ LISTA ;

	LISTA *lista_criar(int depth);
	bool lista_inserir(LISTA *lista, WORD *word);
	WORD *lista_remover(LISTA *lista, char* title);
	void lista_apagar(LISTA **lista);
	WORD *lista_busca(LISTA *lista, char* title);

	int lista_tamanho(LISTA *lista);
	bool lista_vazia(LISTA *lista);
	bool lista_cheia(LISTA *lista);
	void lista_imprimir(LISTA *lista);
	bool lista_imprimir_de_caracter(LISTA *lista, char c);
	  
#endif
