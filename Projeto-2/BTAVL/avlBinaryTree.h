#ifndef BINARY_TREE_H
  #define BINARY_TREE_H

  #include <stdbool.h>

  typedef struct biTree_* Tree;
  typedef struct cell_* Cell;


  bool insert_tree(Tree tree, int input);
  int search_tree(Tree tree, int input);
  int remove_tree(Tree tree, int input);

  int depth(Tree tree);


#endif

