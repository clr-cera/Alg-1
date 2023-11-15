#include "word.h"

struct word_{
	char title[MAX_TITLE];
	char verbete[MAX_VERBETE];
};

//Cria e retorna a palavra
WORD *word_criar(char* title, char* verbete)
{
	WORD* word = malloc(sizeof(WORD));
	if(word != NULL){
		strcpy(word->title, title);
		strcpy(word->verbete, verbete);
	}
	return word;
}

//Imprime a palavra e o verbete
void word_imprimir(WORD *word)
{
	if(word != NULL)
		printf("%s %s\n", word_get_title(word), word_get_verbete(word));
}

//Imprime apenas o verbete, sem a palavra
void word_imprimir_verbete(WORD *word)
{
	if(word != NULL)
		printf("%s\n", word_get_verbete(word));
}

//Retorna a palavra
char* word_get_title(WORD *word)
{
	if(word != NULL)
		return(word->title);
}

//Retorna o verbete
char* word_get_verbete(WORD *word)
{
	if(word != NULL)
		return(word->verbete);
}

//Apaga a palavra
bool word_apagar(WORD **word)
{
	if( (*word) != NULL){
		free(*word);
		(*word) = NULL;
		return true;
	}
	return false;
}

//Modifica a palavra da palavra
bool word_set_title(WORD* word, char* title)
{
	if(word != NULL){
		strcpy(word->title, title);
		return true;
	}
	return false;
}

//Modifica o verbete
bool word_set_verbete(WORD* word, char* verbete)
{
	if(word != NULL){
		strcpy(word->verbete, verbete);
		return true;
	}
	return false;
}

//Compara as palavras de duas palavras
int word_compare(WORD *word1, WORD *word2){
	if(word1 == NULL || word2 == NULL)
		return -32000;
	return strcmp(word_get_title(word1), word_get_title(word2));
}
