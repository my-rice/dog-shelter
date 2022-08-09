#include <stdio.h>
#include <stdlib.h>
#include "tree.h"
#include "info.h"


TTree tree_create()
{
   return NULL;
}


TTree tree_destroy(TTree tree) {
   if(tree==NULL)
     return NULL;
   else if((tree->left==NULL) && (tree->right==NULL)) {
     free(tree);
     return NULL;
   }
   else {
     tree->left = tree_destroy(tree->left);
     tree->right = tree_destroy(tree->right);
     free(tree);
     return NULL;
   }
}


void tree_print(TTree tree)
{
  if(tree!=NULL)
  {
    tree_print(tree->left);
    print_info(tree->info);
    tree_print(tree->right);
  }
}


TNode* tree_search(TTree tree, TKey key)
{
  if((tree==NULL) || equal(tree->info.key, key))
    return tree;
  else
  {
    if(greater(key, tree->info.key))
      return tree_search(tree->right, key);
    else
      return tree_search(tree->left, key);
  }
}


TTree tree_insert(TTree tree, TInfo info)
{
  if(tree==NULL){
    TNode* newnode;
    newnode=(TNode*) malloc(sizeof(TNode));
    if(newnode==NULL){
      printf("Errore di allocazione");
      exit(1);
    }
    newnode->right=newnode->left=NULL;
    newnode->info=info;
    return newnode;
  }
  else if(!greater(info.key,tree->info.key)){
    tree->left=tree_insert(tree->left,info);
    return tree;
  }
  else{
    tree->right=tree_insert(tree->right,info);
    return tree;
  }
}


TTree tree_delete(TTree tree, TKey key) {
  if(tree==NULL)
    return NULL;
  else if(greater(tree->info.key, key)) {
    tree->left=tree_delete(tree->left, key);
    return tree;
  } 
  else if(greater(key, tree->info.key)) {
    tree->right=tree_delete(tree->right, key);
    return tree;
  }
  else{ /* tree->info.key==key */
    TTree min_right;
    if((tree->right==NULL) && (tree->left==NULL)) {
      free(tree); /* Cancellazione di una foglia */
      return NULL;
    }
    if(tree->right==NULL) { /* Cancellazione di un nodo con
                               il solo figlio sinistro */
      TTree alias;
      alias = tree->left;
      free(tree);
      return alias;
    }
    if(tree->left==NULL) { /* Cancellazione di un nodo con
                              il solo figlio destro */
      TTree alias;
      alias=tree->right;
      free(tree);
      return alias;
    }
    /* Cancellazione di un nodo con entrambi i figli */
    min_right=tree_min(tree->right); /* Ricerca del minimo del 
                                        sottoalbero destro */
    tree->info=min_right->info; /* Copia del minimo nel campo info
                                   del nodo da eliminare */
    /* Eliminazione del nodo da cui � stato copiato il minimo */
    tree->right=tree_delete(tree->right,min_right->info.key);
    return tree;
  }
}


bool tree_empty(TTree tree)
{
   if(tree==NULL)
      return true;
   else
      return false;     
}


bool tree_full(TTree tree)
{
     return false;
}


TNode* tree_min(TTree tree)
{
  if(tree==NULL)
    return NULL;
  else
  {
    if(tree->left!=NULL)
      return tree_min(tree->left);
    else
      return tree;
  }
}


