#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "treemap.h"

typedef struct TreeNode TreeNode;


struct TreeNode {
    Pair* pair;
    TreeNode * left;
    TreeNode * right;
    TreeNode * parent;
};

struct TreeMap {
    TreeNode * root;
    TreeNode * current;
    int (*lower_than) (void* key1, void* key2);
};

int is_equal(TreeMap* tree, void* key1, void* key2){
    if(tree->lower_than(key1,key2)==0 &&  
        tree->lower_than(key2,key1)==0) return 1;
    else return 0;
}


TreeNode * createTreeNode(void* key, void * value) {
    TreeNode * new = (TreeNode *)malloc(sizeof(TreeNode));
    if (new == NULL) return NULL;
    new->pair = (Pair *)malloc(sizeof(Pair));
    new->pair->key = key;
    new->pair->value = value;
    new->parent = new->left = new->right = NULL;
    return new;
}

TreeMap * createTreeMap(int (*lower_than) (void* key1, void* key2)) {

    
    TreeMap * nuevoMapa = (TreeMap*) malloc(sizeof(TreeMap));
    if(nuevoMapa == NULL) return NULL;

    nuevoMapa->root = NULL;
    nuevoMapa->current = NULL;
    nuevoMapa->lower_than = lower_than;
  
    return nuevoMapa;
}


void insertTreeMap(TreeMap * tree, void* key, void * value) {
  TreeNode* nuevoNodo = createTreeNode(key, value);
  
    if (tree->root == NULL) 
    { 
        tree->root = nuevoNodo;
        tree->current = nuevoNodo;
        return;
    }
    
    TreeNode* current_node = tree->root;
    TreeNode* parent_node = NULL;

   if(searchTreeMap(tree, key) != NULL) return;
    
    while (current_node != NULL) 
    { 
        if (tree->lower_than(key, current_node->pair->key)) {
            parent_node = current_node;
            current_node = current_node->left;
        } else if (tree->lower_than(current_node->pair->key, key)) {
            parent_node = current_node;
            current_node = current_node->right;
        }
    }
    
    nuevoNodo->parent = parent_node;
    
    if (tree->lower_than(key, parent_node->pair->key)) {
        parent_node->left = nuevoNodo;
    } else {
        parent_node->right = nuevoNodo;
    }
    
    tree->current = nuevoNodo;
}

TreeNode * minimum(TreeNode * x){
    if(x == NULL)
    {
      return NULL;
    }   
    while(x->left != NULL)
      x = x->left;
  
  return x;
}


void removeNode(TreeMap * tree, TreeNode* node) {
  if(node->right == NULL || node->left==NULL)
  {
    treeNode * parent = node->parent;
    if(parent->left == node)
    {
      parent->left = NULL;
    }else
    {
      parent->right = NULL;
    }
    free(node);
  }

}

void eraseTreeMap(TreeMap * tree, void* key){
    if (tree == NULL || tree->root == NULL) return;

    if (searchTreeMap(tree, key) == NULL) return;
    TreeNode* node = tree->current;
    removeNode(tree, node);

}




Pair * searchTreeMap(TreeMap * tree, void* key) {
  tree->current = tree->root;
  if(tree->root == NULL) return NULL;

  while(tree->current != NULL)
    {
      if(is_equal(tree, tree->current->pair->key, key))
      {
        return(tree->current->pair);
      }

      if(tree->lower_than(tree->current->pair->key, key))
      {
        tree->current = tree->current->right;
      }
      else
      {
        tree->current = tree->current->left;
      }
    }
    
  return NULL;
}


Pair * upperBound(TreeMap * tree, void* key) {
    return NULL;
}

Pair * firstTreeMap(TreeMap * tree) {
    return NULL;
}

Pair * nextTreeMap(TreeMap * tree) {
    return NULL;
}
