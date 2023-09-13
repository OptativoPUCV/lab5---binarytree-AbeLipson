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
    TreeMap *new = (TreeMap *)malloc(sizeof(TreeMap));

    if (new==NULL){ //memory allocation error
        return NULL;
    }

    new->root = NULL;
    new->current = NULL;
    new->lower_than = lower_than;
    return new;
}


void insertTreeMap(TreeMap * tree, void* key, void * value) {
    TreeNode *current = tree->root;
    TreeNode *new = createTreeNode(key,value);

    if(searchTreeMap(tree,key) == NULL){
        TreeNode *parent = current;
        while(current != NULL){
            parent = current;
            int cmp_result = tree->lower_than(key, current->pair->key);
            if (cmp_result == 1){
                current = current->left;
            }
            else{
                current = current->right;
            }
        }
        if (parent == NULL){
            tree->root = new;
            tree->current = new;
        }
        else{
            if(tree->lower_than(key, parent->pair->key)){
                parent->left = new;
                new->parent = parent;
            }
            else{
                parent->right = new;
                new->parent = parent;
            }
            current = new;
            tree->current = new;
        }
    }
}

TreeNode * minimum(TreeNode * x){
    TreeNode *currentMin = x;
    while(currentMin->left !=NULL){
        currentMin = currentMin->left;
    }
    return currentMin;
}


void removeNode(TreeMap * tree, TreeNode* node) {
//if the node has no children
if(node->left == NULL && node->right ==NULL){
    if(node->parent !=NULL){
        if(node->parent->left == node){
            node->parent->left = NULL;
        }
        else{
            node->parent->right = NULL;
        }
    }
    else{
        tree->root = NULL;
    }
    free(node->pair);
    free(node);
}


else if(node->left !=NULL || node->right==NULL){
    if(node->parent !=NULL){
        if (node->parent->left == node){
            node->parent->left = node->left;
            node->left->parent = node->parent;
        }
        else{
            node->parent->right = node->right;
            node->right->parent = node->parent;
            
        }

        node->left->parent = node->parent;
    }
    else{
        tree->root = node->left;
        node->left->parent = NULL;
    }
    free(node->pair);
    free(node);
}
else if(node->left ==NULL || node->right!=NULL){
    if(node->parent !=NULL){
        if (node->parent->right == node){
            node->parent->right = node->right;
            node->right->parent = node->parent;
        }
        else{
            node->parent->left = node->left;
            node->left->parent = node->parent;
            //do the same but for if it is the right child of the parent
        }

        node->left->parent = node->parent;
    }
    else{
        tree->root = node->right;
        node->right->parent = NULL;
    }
    free(node->pair);
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
    TreeNode *current = tree->root;
    
    while(current!=NULL){
        int cmp_result = tree->lower_than(key, current->pair->key);

        if(is_equal(tree,key,current->pair->key)){
            tree->current = current;
            return current->pair;
        }
        else if (cmp_result == 1){
            current = current->left;
        }
        else{
            current = current->right;   
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
