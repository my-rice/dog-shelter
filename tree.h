#ifndef TREE_H
#define TREE_H

#include "info.h"

struct SNode {
   TInfo info;
   struct SNode *left;
   struct SNode *right;
};
typedef struct SNode TNode;
typedef TNode* TTree;

TTree tree_create();
TTree tree_destroy(TTree tree);
void tree_visit(TTree tree);
TNode* tree_search(TTree tree, TKey Key);
TTree tree_insert(TTree tree, TInfo info);
TTree tree_delete(TTree tree, TKey key);
bool tree_empty(TTree tree);
bool tree_full(TTree tree);
TNode* tree_min(TTree tree);
void tree_print(TTree tree);


#endif
