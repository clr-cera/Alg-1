#include "word.h"

struct word_{
	char title[MAX_TITLE];
	char verbete[MAX_VERBETE];
};

WORD *word_criar(char* title, char* verbete)
{
	WORD* word = malloc(sizeof(WORD));
	if(word != NULL){
		strcpy(word->title, title);
		strcpy(word->verbete, verbete);
	}
	return word;
}
void word_imprimir(WORD *word)
{
	if(word != NULL)
		printf("%s %s\n", word_get_title(word), word_get_verbete(word));
}

char* word_get_title(WORD *word)
{
	if(word != NULL)
		return(word->title);
}

char* word_get_verbete(WORD *word)
{
	if(word != NULL)
		return(word->verbete);
}

bool word_apagar(WORD **word)
{
	if( (*word) != NULL){
		free(*word);
		(*word) = NULL;
		return true;
	}
	return false;
}

bool word_set_title(WORD* word, char* title)
{
	if(word != NULL){
		strcpy(word->title, title);
		return true;
	}
	return false;
}

bool word_set_verbete(WORD* word, char* verbete)
{
	if(word != NULL){
		strcpy(word->verbete, verbete);
		return true;
	}
	return false;
}
