#include "stdlib.h"
#include "stdio.h"
#include "avlBinaryTree.h"

// Esta é uma flag que é usada para saber se houve problema na inserção ou remoção 
// ao passar o balanço através da volta da recursão
#define ERROR -99999 

// Essa é a unidade básica da árvore AVL, 
// ela possui um item, um balanço, um ponteiro para a direita e um ponteiro para a esquerda
typedef struct cell_{
  Item value;
  int balance;
  struct cell_* right;
  struct cell_* left;
}cellObj;
typedef cellObj* Cell;

// Essa é a struct árvore, a qual contém a sua raiz
typedef struct biTree_ {
  Cell root;
}biTreeObj;
typedef biTreeObj* Tree;

int depthRec(Cell cell);

Tree create_tree();

void printCell(Cell cell);
void changeCell(Cell cell, int new);

Item searchRec(Cell cell, int input);

int insertRec(Cell* cell, int input);
int insertInPlace(Cell* cell, int input);

void rotateRight(Cell* cell);
void rotateLeft(Cell* cell);

int removeRec(Cell* cell, int input);
int removeInPlace(Cell* cell);
Cell removeRighteous(Cell* cell);

void tree_to_queue_rec(Cell cell, queue Queue);

void erase_tree_rec(Cell cell);

void print_tree_rec(Cell cell);

// Essa função retorna o maior valor entre dois inteiros
int max(int a, int b){
  if (a >= b) return a;
  else return b;
}

// Essa função cria uma árvore AVL
Tree create_tree() {
  Tree tree = (Tree) malloc(sizeof(biTreeObj));
  
  tree->root = NULL;
  
  return tree;
}

// Essa função cria uma célula a qual contém um item que contem um inteiro n, 
// ela recebe o inteiro n e retorna a célula
Cell createCell(int n) {
  Cell cell = (Cell) malloc(sizeof(cellObj));
  
  cell->value = item_criar(n);
  cell->balance = 0;
  cell->right = NULL;
  cell->left = NULL;
  
  return cell;
}

// Essa função imprime uma célula
void printCell(Cell cell) {
  printf("%d, ", item_get_chave(cell->value));
}

// Essa função muda o valor de uma célula
void changeCell(Cell cell, int new) {
  if (cell->value != NULL)
    free(cell->value);
  cell->value = item_criar(new);
}

// Essa função apaga uma célula da memória,
// ela recebe um endereço de uma célula e a torna NULL
void removeCell(Cell* cell){
  if ((*cell)->value != NULL)
    free((*cell)->value);
  free(*cell);
  *cell = NULL;
}

// Essa função calcula a profundidade de uma árvore,
// ela recebe uma árvore e retorna a sua profundidade
int depth(Tree tree) {
  if (tree == NULL) return -2;

  return depthRec(tree->root);
}

int depthRec(Cell cell) {
  if (cell == NULL) return -1;
  int leftDepth = depthRec(cell->left);
  int rightDepth = depthRec(cell->right);

  return (max(leftDepth, rightDepth) + 1); // A maior profundidade entre as duas é a significante
}

// Essa função busca um item dado uma chave,
// ela recebe um inteiro e retorna o Item que contém este inteiro
Item search_tree(Tree tree, int input) {
  if (tree == NULL) return NULL;
  
  return searchRec(tree->root, input);
}

// Essa função busca recursivamente por um item dentro da subárvore pertencente à uma célula
// ela recebe uma célula e um inteiro e retorna um item
Item searchRec(Cell cell, int input) {
  if (cell == NULL) return NULL;
  if (item_get_chave(cell->value) == input) return cell->value;

  if (input < item_get_chave(cell->value))
    return searchRec(cell->left, input);

  else 
    return searchRec(cell->right, input);
}

// Essa função insere um novo inteiro em uma árvore, caso o elemento já esteja presente, nada será alterado,
// ela recebe uma árvore e um inteiro e retorna true se a inserção foi realizada
bool insert_tree(Tree tree, int input) {
  if (tree == NULL) return false;
  if (tree->root == NULL) {insertInPlace(&tree->root, input); return true;}

  if (insertRec(&tree->root, input) != ERROR)
    return true;
  else return false;
}

// Essa função busca o espaço para inserir o inteiro e faz rotações se necessário
// ela retorna um inteiro que pode ser o balanço da célula, uma flag de ERROR ou 0
int insertRec(Cell* cell, int input) {
  int balance_below;
  Cell cellObj = *cell;

  if (input == item_get_chave(cellObj->value)) 
    return 0;

  if (input < item_get_chave(cellObj->value)){
    if (cellObj->left == NULL) balance_below = insertInPlace(&cellObj->left, input);
    
    else balance_below = insertRec(&cellObj->left, input);
    
    if (balance_below == 0 || balance_below == ERROR) // Se o balanço abaixo for 0 ou erro, não há necessidade de alterar mais nenhum balanço, portanto apenas retorna o balanço debaixo
      return balance_below;
    else // Senão como a inserção foi a esquerda, soma-se 1 ao balanço
      cellObj->balance +=1;
  }
  
  else if (input > item_get_chave(cellObj->value)){
    if (cellObj->right == NULL) balance_below = insertInPlace(&cellObj->right, input);
  
    else balance_below = insertRec(&cellObj->right, input);
    
    if (balance_below == 0 || balance_below == ERROR) // Se o balanço abaixo for 0 ou erro, não há necessidade de alterar mais nenhum balanço, portanto apenas retorna o balanço debaixo
      return balance_below;
    else // Senão, como a inserção foi a direita, reduz-se 1 ao balanço
      cellObj->balance -=1;
  }

  // Caso a subárvore dessa célula esteja desbalanceada, realiza-se uma rotação
  if (cellObj->balance == 2)
    rotateRight(cell);
  if (cellObj->balance == -2)
    rotateLeft(cell);

  return cellObj->balance;
}

// Essa função cria uma objeto célula e a insere em um endereço
// ela recebe um endereço de uma célula e um inteiro, retorna 1 se havia memória e error se não havia
int insertInPlace(Cell* cell, int input) {
  *cell = createCell(input);
  if (*cell != NULL) return 1;
  else return ERROR;
}

// Essa função rotaciona uma subárvore para a direita
void rotateRight(Cell* cell){
  Cell cellObj = *cell;
  if (cellObj == NULL) return;
  if (cellObj->left == NULL) return;

  bool isSimple = true;

  // Tratamento de rotação dupla
  if (cellObj->left->balance == -1){
    rotateLeft(&cellObj->left);
    isSimple = false;
  }

  // Atualização de balanços
  if (isSimple) 
    cellObj->balance = 0;
  else 
    cellObj->balance = -1;
    
  cellObj->left->balance = 0;

  // Essa é a subárvore a direita da célula à esquerda da raiz
  Cell right_sub_tree = cellObj->left->right;

  // Os ponteiros são alterados para realizar a rotação
  cellObj->left->right = cellObj;
  *cell = cellObj->left;
  cellObj->left = right_sub_tree;
}

// Essa função rotaciona uma subárvore para a direita
void rotateLeft(Cell* cell){
  Cell cellObj = *cell;
  if (cellObj == NULL) return;
  if (cellObj->right == NULL) return;
  
  bool isSimple = true;

  // Tratamento de rotação dupla
  if (cellObj->right->balance == 1){
    rotateRight(&cellObj->right);
    isSimple = false;
  }

  
  // Atualização de balanços
  if (isSimple) 
    cellObj->balance = 0;
  else 
    cellObj->balance = 1;
    
  cellObj->right->balance = 0;
  
  // Essa é a subárvore a esquerda da célula à direita da raiz
  Cell left_sub_tree = cellObj->right->left;

  // Os ponteiros são alterados para realizar a rotação
  cellObj->right->left = cellObj;
  *cell = cellObj->right;
  cellObj->right = left_sub_tree;
}

// Essa função remove um inteiro de uma árvore caso ele exista,
// ela recebe uma árvore e um inteiro e retorna true se a remoção foi realizada ou false se o inteiro não estava presente
bool remove_tree(Tree tree, int input) {
  if (tree == NULL) return NULL;
  
  if (removeRec(&tree->root, input) != ERROR)
    return true;

  else return false;
}

// Essa função busca uma célula que contém um inteiro específico para removê-la
// ela retorna um inteiro que pode ser o balanço da célula, uma flag de ERROR ou 0
int removeRec(Cell* cell, int input) {
  int balance_below;
  Cell cellObj = *cell;

  if (*cell == NULL) return ERROR;

  if (item_get_chave((*cell)->value) == input)
    return removeInPlace(cell);

  if (input < item_get_chave((*cell)->value)){
    balance_below = removeRec(&(*cell)->left, input);
     
    if (balance_below != 0 || balance_below == ERROR) // Se o balanço anterior for diferente de 0 ou ERROR, não há necessidade de realizar mais alterações em balanços portanto se retorna este balanço
      return balance_below;
    else
      cellObj->balance -=1; // senão, como a remoção foi a esquerda, balanço descresce 1

  }
  
  else {
    balance_below = removeRec(&(*cell)->right, input);
    
    if (balance_below != 0 || balance_below == ERROR) // Se o balanço anterior for diferente de 0 ou ERROR, não há necessidade de realizar mais alterações em balanços portanto se retorna este balanço
      return balance_below;
    else
      cellObj->balance +=1; // senão, como a remoção foi a direita, balanço acresce 1
  }

  // Se a subárvore de célula estiver desbalanceada é feita uma rotação
  if (cellObj->balance == 2)
    rotateRight(cell);
  if (cellObj->balance == -2)
    rotateLeft(cell);
  
  return cellObj->balance;
}

// Essa função remove uma célula de uma posição e retorna 1 para indicar que o balanço deve ser alterado
int removeInPlace(Cell* cell) {
  Cell oldCell = *cell;

  if (oldCell->right == NULL)
    *cell = oldCell->left;
  
  else if (oldCell->left == NULL)
    *cell = oldCell->right;
  
  else {// caso a célula tenha os dois filhos, a célula mais a direita da subárvore esquerda entra no lugar da célula removida
    *cell = removeRighteous(&oldCell->left);
    (*cell)->right = oldCell->right;
    (*cell)->left = oldCell->left;
  }

  removeCell(&oldCell);

  return 1;
}

// Essa função remove a célula mais a direita de uma subárvore e a retorna,
// ela recebe um endereço de uma célula e retorna a célula mais a direita
Cell removeRighteous(Cell* cell){
  Cell currentCell = *cell;

  if (currentCell->right != NULL)
    return removeRighteous(&currentCell->right);

  *cell = currentCell->left; 
  return currentCell;
}

// Essa função coloca todos os elementos de uma árvore em uma fila
// ela recebe uma árvore e retorna a fila contendo todos os elementos em ordem
queue tree_to_queue(Tree tree) {
  if (tree == NULL) return NULL;

  queue Queue = createQueue();
  tree_to_queue_rec(tree->root, Queue);
  return Queue;
}

// Essa função insere todos os elementos na fila recursivamente,
// ela recebe a célula atual e a fila e insere o elemento da célua na fila
void tree_to_queue_rec(Cell cell, queue Queue){
  if (cell == NULL) return;

  tree_to_queue_rec(cell->left, Queue);

  insertQueue(Queue, item_get_chave(cell->value));

  tree_to_queue_rec(cell->right, Queue);
}

// Essa função apaga uma árvore da memória
void erase_tree(Tree tree) {
  if (tree == NULL) return;
  erase_tree_rec(tree->root);
  free(tree);
}

// Essa função apaga os elementos da árvore recursivamente
void erase_tree_rec(Cell cell) {
  if (cell == NULL) return;

  erase_tree_rec(cell->left);
  erase_tree_rec(cell->right);

  removeCell(&cell);
}

// Essa função imprime todos os elementos de uma árvore em ordem
void print_tree(Tree tree) {
  if (tree == NULL) return;

  print_tree_rec(tree->root);
  printf("\n");
}

// Essa função imprime as células recursivamente
void print_tree_rec(Cell cell) {
  if (cell == NULL) return;

  print_tree_rec(cell->left);

  printCell(cell);

  print_tree_rec(cell->right);
}
