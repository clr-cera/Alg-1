#ifndef WORD_H
	#define WORD_H
	
	#include <stdbool.h>
	#include <stdlib.h>
	#include <stdio.h>
	#include <string.h>

	#define MAX_TITLE 50
	#define MAX_VERBETE 140

	
	typedef struct word_ WORD;
  typedef WORD* Word;

	WORD *word_criar(char* title, char* verbete);
	bool word_apagar(WORD **word);
	void word_imprimir(WORD *word);
	void word_imprimir_verbete(WORD *word);
	char* word_get_title(WORD *word);
	char* word_get_verbete(WORD *word);
	bool word_set_title(WORD *word, char* title);
	bool word_set_verbete(WORD *word, char* verbete);

#endif 
