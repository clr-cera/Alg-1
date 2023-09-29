#ifndef LISTA_H
	#define LISTA_H

	#include "word.h"
	#include <stdbool.h>

	typedef struct lista_ LISTA;

	LISTA *lista_criar(void);
	bool lista_inserir(LISTA *lista, WORD *word);
	WORD *lista_remover(LISTA *lista, char* title);
	void lista_apagar(LISTA **lista);
	WORD *lista_busca(LISTA *lista, char* title);

	int lista_tamanho(LISTA *lista);
	bool lista_vazia(LISTA *lista);
	bool lista_cheia(LISTA *lista);
	void lista_imprimir(LISTA *lista);

	  
#endif
