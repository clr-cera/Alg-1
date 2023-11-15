#include "stdlib.h"
#include "stdio.h"
#include "avlBinaryTree.h"

#define ERROR -99999

typedef struct cell_{
  int value;
  int balance;
  struct cell_* right;
  struct cell_* left;
}cellObj;
typedef cellObj* Cell;

typedef struct biTree_ {
  Cell root;
  int depth;
}biTreeObj;
typedef biTreeObj* Tree;

int depthRec(Cell cell);

void printCell(Cell cell);
void changeCell(Cell cell, int new);

int searchRec(Cell cell, int input);

int insertRec(Cell* cell, int input);
int insertInPlace(Cell* cell, int input);

void rotateRight(Cell* cell);
void rotateLeft(Cell* cell);

int removeRec(Cell* cell, int input);
int removeInPlace(Cell* cell);
Cell removeRighteous(Cell* cell);

int max(int a, int b){
  if (a >= b) return a;
  else return b;
}

Cell createCell(int n) {
  Cell cell = (Cell) malloc(sizeof(cellObj));
  
  cell->value = n;
  cell->value = 0;
  cell->right = NULL;
  cell->left = NULL;
  
  return cell;
}

void printCell(Cell cell) {
  printf("%d\n", cell->value);
}

void changeCell(Cell cell, int new) {
  cell->value = new;
}

void removeCell(Cell* cell){
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

int search_tree(Tree tree, int input) {
  if (tree == NULL) return NULL;
  
  return searchRec(tree->root, input);
}

int searchRec(Cell cell, int input) {
  if (cell == NULL) return -1;
  if (cell->value == input) return cell->value;

  if (input < cell->value)
    return searchRec(cell->left, input);

  else 
    return searchRec(cell->right, input);
}

bool insert_tree(Tree tree, int input) {
  if (tree == NULL) return false;
  if (tree->root == NULL) insertInPlace(&tree->root, input);

  return insertRec(&tree->root, input);
}

int insertRec(Cell* cell, int input) {
  int balance_below;
  Cell cellObj = *cell;

  if (input < cellObj->value){
    if (cellObj->left == NULL) balance_below = insertInPlace(&cellObj->left, input);
    
    else balance_below = insertRec(&cellObj->left, input);
    
    if (balance_below == 0 || balance_below == ERROR)
      return balance_below;
    else
      cellObj->balance +=1;
  }
  
  else if (input > cellObj->value){
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

  if (cellObj->left->balance == -1)
    rotateLeft(&cellObj->left);

  Cell right_sub_tree = cellObj->left->right;

  cellObj->left->right = cellObj;
  *cell = cellObj->left;
  cellObj->left = right_sub_tree;
}

void rotateLeft(Cell* cell){
  Cell cellObj = *cell;
  if (cellObj == NULL) return;
  if (cellObj->right == NULL) return;
  
  if (cellObj->right->balance == 1)
    rotateRight(&cellObj->right);

  Cell left_sub_tree = cellObj->right->left;

  cellObj->right->left = cellObj;
  *cell = cellObj->right;
  cellObj->right = left_sub_tree;
}

int remove_tree(Tree tree, int input) {
  if (tree == NULL) return NULL;
  
  return removeRec(&tree->root, input);
}

int removeRec(Cell* cell, int input) {
  if (*cell == NULL) return -1;

  if ((*cell)->value == input)
    return removeInPlace(cell);

  if (input < (*cell)->value)
    return removeRec(&(*cell)->left, input);
  
  else
    return removeRec(&(*cell)->right, input);
}

int removeInPlace(Cell* cell) {
  Cell oldCell = *cell;
  int returnal = oldCell->value;

  if (oldCell->right == NULL)
    *cell = oldCell->left;
  
  else if (oldCell->left == NULL)
    *cell = oldCell->right;
  
  else 
    *cell = removeRighteous(&oldCell->left);

  removeCell(&oldCell);
  return returnal;
}

Cell removeRighteous(Cell* cell){
  Cell currentCell = *cell;

  if (currentCell->right != NULL)
    return removeRighteous(&currentCell->right);

  *cell = currentCell->left; 
  return currentCell;
}
