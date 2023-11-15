#include "set.h"
#include "../BTAVL/avlBinaryTree.h"

struct set{
	AVL* tree;
}

SET *set_criar(void){
	SET* conjunto = malloc(sizeof(SET));
	if(conjunto != NULL)
		conjunto->tree = avl_criar();
	return conjunto;
}
bool set_pertence(SET *A, int elemento){
	return avl_busca(A->tree, elemento);
}
bool set_inserir (SET *s, int elemento){
	return avl_inserir(s->tree, elemento)
}
bool set_remover(SET *s, int elemento){
	return avl_remover(s->tree, elemento)
}
void set_apagar(SET **s){
	avl_apagar((*s)->tree);
	(*s)->tree = NULL;
	free((*s));
	(*s) = NULL;
}
void set_imprimir(SET *s){
	avl_imprimir(s->tree);
}
//A AVL dentro do Set garante que não haja itens repetidos, logo na operação união basta inserir todos os itens de ambas os conjuntos em um terceiro.
SET *set_uniao(SET *A, SET *B){
	QUEUE* queue_A = tree_to_queue(A);
	QUEUE* queue_B = tree_to_queue(B);
	SET* uniao = set_criar();
	while(!queue_empty(queue_A) && !queue_empty(queue_B)){
		
		ITEM* rm1 = queue_pop(queue_A);
		set_inserir(uniao, item_get_chave(rm1));
		item_remover(rm1);
	
		ITEM* rm2 = queue_pop(queue_B);
		set_inserir(uniao, item_get_chave(rm2));
		item_remover(rm2);
		
	}
	return uniao;
}
SET *set_interseccao(SET *A, SET *B){
	QUEUE* queue_A = tree_to_queue(A);
	QUEUE* queue_B = tree_to_queue(B);
	SET* interseccao = set_criar();
	ITEM* rm1 = queue_pop(queue_A);
	ITEM* rm2 = queue_pop(queue_B);
	while(!queue_empty(queue_A) && !queue_empty(queue_B)){
		if(!queue_empty(queue_A)){
			if(item_get_chave(rm1) > item_get_chave(rm2)){
				item_remover(rm2);
				rm2 = queue_pop(queue_B);
			}
			if(item_get_chave(rm1) < item_get_chave(rm2)){
				item_remover(rm1);
				rm1 = queue_pop(queue_A);
			}
			if(item_get_chave(rm1) == item_get_chave(rm2)){
				set_inserir(uniao, item_get_chave(rm1));
				item_remover(rm1);
				item_remover(rm2);
				rm1 = queue_pop(queue_A);
				rm2 = queue_pop(queue_B);
			}
		}
	}
	return uniao;
}
