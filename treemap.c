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
  if(node == NULL) return;
  TreeNode * parent = node->parent;
  
  if(node->right == NULL && node->left==NULL)
  {
    if(parent->left == node)
    {
      parent->left = NULL;
    }else
    {
      parent->right = NULL;
    }
    free(node);
    return;
  }

  if(node->left == NULL || node->right == NULL)
  {
    TreeNode * hijo;
  
    if(node->left != NULL)
    {
      hijo = node->left;
    }else
    {
      hijo = node->right;
    }
    
    if(parent != NULL)
    {
      if(parent->left == node)
      {
        parent->left = hijo;
      }else
      {
        parent->right = hijo;
      }
      hijo->parent = parent;
    }
    else
    {
      tree->root = hijo;
      if(hijo != NULL) hijo->parent = NULL;
    }
    free(node);
  }

  if(node->left != NULL && node->right != NULL)
  {
    TreeNode * minimo = minimum(node->right);
    node->pair = minimo->pair;
    removeNode(tree, minimo);
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
  Pair * parBuscado = searchTreeMap(tree, key);

  if(parBuscado != NULL)
  {
    return parBuscado;
  }else
  {
    TreeNode * ub_node;
    TreeNode * current = tree->current;
    if(current == NULL) return NULL;

    while(current!=NULL)
      {
        if(tree->lower_than(key, current->pair->key))
        {
          ub_node = current;
          current = current->left;
        }else
        {
          current=current->right;
        }
      }
    
    if(ub_node != NULL)
    {
      return ub_node->pair;
    }
    else
    {
      return NULL;
    }
  }
}

Pair * firstTreeMap(TreeMap * tree) {
  if(tree->root == NULL) return NULL;
  if(tree->root->left == NULL && tree->root->right) return tree->root->pair;

  TreeNode * node = tree->root;
  TreeNode * primero;
  
  if(node->left != NULL)
  {
    primero = minimum(node->left);
  }else
  {
    primero = minimum(node->right);
  }
  
    return primero->pair;
}

Pair * nextTreeMap(TreeMap * tree) {
  if(tree->current == NULL) return NULL;
  
  TreeNode * nodoAux = tree->current;

  if(nodoAux->right != NULL)
  {
    TreeNode * nextNode = minimum(nodoAux->right);
    tree->current = nextNode;
    return nextNode->pair;
  }else
  {  
    TreeNode * parent = tree->current->parent;
    while(parent!=NULL)
      {
        if(tree->lower_than(nodoAux->pair->key, parent->pair->key))
        {
          tree->current = parent;
          return parent->pair;
        }
        else
        {
          parent = parent->parent;
        }
      }
  }

  if(tree->current->parent == NULL) return NULL;

  return NULL;
}
