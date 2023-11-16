#include "set.h"
#include "../BTAVL/avlBinaryTree.h"
#include "../Queue/queue.h"
#include <stdlib.h>
//O struct set consiste apenas de uma AVL
struct set{
	AVL tree;
};
//A operação de criar um set consiste apenas em criar a arvore dentro do set 
SET *set_criar(void){
	SET* conjunto = malloc(sizeof(SET));
	if(conjunto != NULL)
		conjunto->tree = create_tree();
	return conjunto;
}
//A operação set pertence consiste apenas em realizar uma busca na árvore, caso a busca retorne nulo indica que o item não existe na árvore e, portanto não está no set
bool set_pertence(SET *A, int elemento){
  if(search_tree(A->tree, elemento) != NULL) return true;
  
  else return false;
}
//A operação de inserir no set consiste apenas de inserir o elemento na árvore dentro do set
bool set_inserir (SET *s, int elemento){
	return insert_tree(s->tree, elemento);
}
//A operação de remover do set consiste apenas de remover o elemento da árvore dentro do set
bool set_remover(SET *s, int elemento){
	return remove_tree(s->tree, elemento);
}
//A operação de apagar o set consiste apenas em apagar a árvore dentro do set
void set_apagar(SET **s){
	erase_tree((*s)->tree);
	(*s)->tree = NULL;
	free((*s));
	(*s) = NULL;
}
//A operação de imprimir o set consiste apenas em imprimir a árvore dentro do set
void set_imprimir(SET *s){
	print_tree(s->tree);
}
//A AVL dentro do Set garante que não haja itens repetidos, logo na operação união basta inserir todos os itens de ambas os conjuntos em um terceiro.
SET *set_uniao(SET *A, SET *B){
	//Ambas as árvores são transformadas em filas, pois seus dados serão consumidos na ordem de inserção na fila (ordem crescente)
	QUEUE* queue_A = tree_to_queue(A->tree);
	QUEUE* queue_B = tree_to_queue(B->tree);
	SET* uniao = set_criar();
	//Todos os itens das filas são inseridos no set união
	while(!queue_empty(queue_A) || !queue_empty(queue_B)){ 
		if (!queue_empty(queue_A))
      set_inserir(uniao, removeQueue(queue_A));
    	if (!queue_empty(queue_B))
  		set_inserir(uniao, removeQueue(queue_B));
	}
  //a fila é apagada para liberar memória
  eraseQueue(queue_A);
  eraseQueue(queue_B);
	
  return uniao;
}
//função que define a operação de intersecção entre os sets
SET *set_interseccao(SET *A, SET *B){
	//Ambas as árvores são transformadas em filas, pois seus dados serão consumidos na ordem de inserção na fila (ordem crescente)
	QUEUE* queue_A = tree_to_queue(A->tree);
	QUEUE* queue_B = tree_to_queue(B->tree);
	SET* interseccao = set_criar();
	//Os inteiros rm1 e rm2 são inicializados com o primeiro elemento das filas, pois serão comparados em breve e, portanto, não podem estar com lixo em sua posição de memória
	int rm1 = removeQueue(queue_A);
	int rm2 = removeQueue(queue_B);
	//O loop while(true) define uma maior flexibilidade na definição do momento onde a condição de parada é definida, garantindo que todos os itens das filas sejam analizados, mesmo o último.
	while(true){	
	//Caso rm1 > rm2, rm2 não pertence a intersecção e, portanto, pode ser descartado sendo substituido pelo próximo item da fila B
    if(rm1 > rm2){
      	if (queue_empty(queue_B)) break;
		rm2 = removeQueue(queue_B);
    }
    //Caso rm1 < rm2, rm1 não pertence a intersecção e, portanto, pode ser descartado sendo substituido pelo próximo item da fila A
    else if(rm1 < rm2){
      	if (queue_empty(queue_A)) break;
		rm1 = removeQueue(queue_A);
    }
    //Caso rm1 == rm2, ambos pertencem a intersecção, porém apenas um precisa ser inserido, pois o outro é igual. Assim, após a inserção ambos são substituidos pelos próximos itens das filas.
    else {
		set_inserir(interseccao, rm1);
      	if (queue_empty(queue_A) || queue_empty(queue_B)) break;
		rm1 = removeQueue(queue_A);
		rm2 = removeQueue(queue_B);
		}
	}
  //as filas são apagadas para liberação de memória
  eraseQueue(queue_A);
  eraseQueue(queue_B);
	
  return interseccao;
}
