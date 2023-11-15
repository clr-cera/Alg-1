#include "stdlib.h"
#include "stdio.h"
#include "avlBinaryTree.h"

#define ERROR -99999

typedef struct cell_{
  Item value;
  int balance;
  struct cell_* right;
  struct cell_* left;
}cellObj;
typedef cellObj* Cell;

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

int max(int a, int b){
  if (a >= b) return a;
  else return b;
}

Tree create_tree() {
  Tree tree = (Tree) malloc(sizeof(biTreeObj));
  
  tree->root = NULL;
  
  return tree;
}


Cell createCell(int n) {
  Cell cell = (Cell) malloc(sizeof(cellObj));
  
  cell->value = item_criar(n);
  cell->balance = 0;
  cell->right = NULL;
  cell->left = NULL;
  
  return cell;
}

void printCell(Cell cell) {
  printf("%d\n", item_get_chave(cell->value));
}

void changeCell(Cell cell, int new) {
  if (cell->value != NULL)
    free(cell->value);
  cell->value = item_criar(new);
}

void removeCell(Cell* cell){
  if ((*cell)->value != NULL)
    free((*cell)->value);
  free(*cell);
  *cell = NULL;
}


int depth(Tree tree) {
  if (tree == NULL) return -2;

  return depthRec(tree->root);
}

int depthRec(Cell cell) {
  if (cell == NULL) return -1;
  int leftDepth = depthRec(cell->left);
  int rightDepth = depthRec(cell->right);

  return (max(leftDepth, rightDepth) + 1); 
}

Item search_tree(Tree tree, int input) {
  if (tree == NULL) return NULL;
  
  return searchRec(tree->root, input);
}

Item searchRec(Cell cell, int input) {
  if (cell == NULL) return NULL;
  if (item_get_chave(cell->value) == input) return cell->value;

  if (input < item_get_chave(cell->value))
    return searchRec(cell->left, input);

  else 
    return searchRec(cell->right, input);
}

bool insert_tree(Tree tree, int input) {
  if (tree == NULL) return false;
  if (tree->root == NULL) {insertInPlace(&tree->root, input); return true;}

  if (insertRec(&tree->root, input) != ERROR)
    return true;
  else return false;
}

int insertRec(Cell* cell, int input) {
  int balance_below;
  Cell cellObj = *cell;

  if (input == item_get_chave(cellObj->value)) 
    return 0;

  if (input < item_get_chave(cellObj->value)){
    if (cellObj->left == NULL) balance_below = insertInPlace(&cellObj->left, input);
    
    else balance_below = insertRec(&cellObj->left, input);
    
    if (balance_below == 0 || balance_below == ERROR)
      return balance_below;
    else
      cellObj->balance +=1;
  }
  
  else if (input > item_get_chave(cellObj->value)){
    if (cellObj->right == NULL) balance_below = insertInPlace(&cellObj->right, input);
  
    else balance_below = insertRec(&cellObj->right, input);
    
    if (balance_below == 0 || balance_below == ERROR)
      return balance_below;
    else
      cellObj->balance -=1;
  }

  if (cellObj->balance == 2)
    rotateRight(cell);
  if (cellObj->balance == -2)
    rotateLeft(cell);

  return cellObj->balance;
}

int insertInPlace(Cell* cell, int input) {
  *cell = createCell(input);
  if (*cell != NULL) return 1;
  else return ERROR;
}

void rotateRight(Cell* cell){
  Cell cellObj = *cell;
  if (cellObj == NULL) return;
  if (cellObj->left == NULL) return;

  bool isSimple = true;

  if (cellObj->left->balance == -1){
    rotateLeft(&cellObj->left);
    isSimple = false;
  }

  if (isSimple) 
    cellObj->balance = 0;
  else 
    cellObj->balance = -1;
    
  cellObj->left->balance = 0;

  Cell right_sub_tree = cellObj->left->right;

  cellObj->left->right = cellObj;
  *cell = cellObj->left;
  cellObj->left = right_sub_tree;
}

void rotateLeft(Cell* cell){
  Cell cellObj = *cell;
  if (cellObj == NULL) return;
  if (cellObj->right == NULL) return;
  
  bool isSimple = true;

  if (cellObj->right->balance == 1){
    rotateRight(&cellObj->right);
    isSimple = false;
  }

  
  if (isSimple) 
    cellObj->balance = 0;
  else 
    cellObj->balance = 1;
    
  cellObj->right->balance = 0;
  
  Cell left_sub_tree = cellObj->right->left;

  cellObj->right->left = cellObj;
  *cell = cellObj->right;
  cellObj->right = left_sub_tree;
}

bool remove_tree(Tree tree, int input) {
  if (tree == NULL) return NULL;
  
  if (removeRec(&tree->root, input) != ERROR)
    return true;

  else return false;
}

int removeRec(Cell* cell, int input) {
  int balance_below;
  Cell cellObj = *cell;

  if (*cell == NULL) return ERROR;

  if (item_get_chave((*cell)->value) == input)
    return removeInPlace(cell);

  if (input < item_get_chave((*cell)->value)){
    balance_below = removeRec(&(*cell)->left, input);
     
    if (balance_below != 0 || balance_below == ERROR)
      return balance_below;
    else
      cellObj->balance -=1; 

  }
  
  else {
    balance_below = removeRec(&(*cell)->right, input);
    
    if (balance_below != 0 || balance_below == ERROR)
      return balance_below;
    else
      cellObj->balance +=1; 
  }

  if (cellObj->balance == 2)
    rotateRight(cell);
  if (cellObj->balance == -2)
    rotateLeft(cell);
  
  return cellObj->balance;
}

int removeInPlace(Cell* cell) {
  Cell oldCell = *cell;

  if (oldCell->right == NULL)
    *cell = oldCell->left;
  
  else if (oldCell->left == NULL)
    *cell = oldCell->right;
  
  else 
    *cell = removeRighteous(&oldCell->left);
  
  (*cell)->right = oldCell->right;
  (*cell)->left = oldCell->left;

  removeCell(&oldCell);

  return 1;
}

Cell removeRighteous(Cell* cell){
  Cell currentCell = *cell;

  if (currentCell->right != NULL)
    return removeRighteous(&currentCell->right);

  *cell = currentCell->left; 
  return currentCell;
}

queue tree_to_queue(Tree tree) {
  if (tree == NULL) return NULL;

  queue Queue = createQueue();
  tree_to_queue_rec(tree->root, Queue);
  return Queue;
}

void tree_to_queue_rec(Cell cell, queue Queue){
  if (cell == NULL) return;

  tree_to_queue_rec(cell->left, Queue);

  insertQueue(Queue, item_get_chave(cell->value));

  tree_to_queue_rec(cell->right, Queue);
}

void erase_tree(Tree tree) {
  if (tree == NULL) return;
  erase_tree_rec(tree->root);
  free(tree);
}

void erase_tree_rec(Cell cell) {
  if (cell == NULL) return;

  erase_tree_rec(cell->left);
  erase_tree_rec(cell->right);

  removeCell(&cell);
}

void print_tree(Tree tree) {
  if (tree == NULL) return;

  print_tree_rec(tree->root);
  printf("\n");
}

void print_tree_rec(Cell cell) {
  if (cell == NULL) return;

  print_tree_rec(cell->left);

  printf("%d, ", item_get_chave(cell->value));

  print_tree_rec(cell->right);
}
