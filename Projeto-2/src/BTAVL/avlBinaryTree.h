#ifndef BINARY_TREE_H
  #define BINARY_TREE_H

  #include <stdbool.h>
  #include "../Queue/queue.h"
  #include "../Item/item.h"

  typedef struct biTree_* Tree;
  typedef Tree AVL;
  typedef struct cell_* Cell;


  Tree create_tree();
  void erase_tree(Tree tree);

  bool insert_tree(Tree tree, int input);
  Item search_tree(Tree tree, int input);
  bool remove_tree(Tree tree, int input);

  void print_tree(Tree tree);
  void print_tree_pretty(Tree tree);
  queue tree_to_queue(Tree tree);

  int depth(Tree tree);


#endif

