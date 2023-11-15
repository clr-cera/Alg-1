#include "set.h"
#include "../BTAVL/avlBinaryTree.h"
#include "../Queue/queue.h"
#include <stdlib.h>

struct set{
	AVL tree;
};

SET *set_criar(void){
	SET* conjunto = malloc(sizeof(SET));
	if(conjunto != NULL)
		conjunto->tree = create_tree();
	return conjunto;
}

bool set_pertence(SET *A, int elemento){
	return search_tree(A->tree, elemento);
}

bool set_inserir (SET *s, int elemento){
	return insert_tree(s->tree, elemento);
}

bool set_remover(SET *s, int elemento){
	return remove_tree(s->tree, elemento);
}

void set_apagar(SET **s){
	erase_tree((*s)->tree);
	(*s)->tree = NULL;
	free((*s));
	(*s) = NULL;
}
void set_imprimir(SET *s){
	print_tree(s->tree);
}
//A AVL dentro do Set garante que não haja itens repetidos, logo na operação união basta inserir todos os itens de ambas os conjuntos em um terceiro.
SET *set_uniao(SET *A, SET *B){
	QUEUE* queue_A = tree_to_queue(A->tree);
	QUEUE* queue_B = tree_to_queue(B->tree);
	SET* uniao = set_criar();

	while(!queue_empty(queue_A) || !queue_empty(queue_B)){ 
		if (!queue_empty(queue_A))
      set_inserir(uniao, removeQueue(queue_A));
    if (!queue_empty(queue_B))
  		set_inserir(uniao, removeQueue(queue_B));
	}
  
  eraseQueue(queue_A);
  eraseQueue(queue_B);
	
  return uniao;
}
SET *set_interseccao(SET *A, SET *B){
	QUEUE* queue_A = tree_to_queue(A->tree);
	QUEUE* queue_B = tree_to_queue(B->tree);
	SET* interseccao = set_criar();

	int rm1 = removeQueue(queue_A);
	int rm2 = removeQueue(queue_B);

	while(!queue_empty(queue_A) && !queue_empty(queue_B)){
		if(!queue_empty(queue_A)){
			
      if(rm1 > rm2)
				rm2 = removeQueue(queue_B);
			
      else if(rm1 < rm2)
				rm1 = removeQueue(queue_A);
			
      else {
				set_inserir(interseccao, rm1);
				rm1 = removeQueue(queue_A);
				rm2 = removeQueue(queue_B);
			}
		}
	}
  
  eraseQueue(queue_A);
  eraseQueue(queue_B);
	
  return interseccao;
}
