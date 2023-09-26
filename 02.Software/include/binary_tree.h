#ifndef __BINARY_TREE_H__
#define __BINARY_TREE_H__

#include <stdio.h>
typedef struct node bt_node;
struct node {
    char data;
    bt_node* left;
    bt_node* right;
};

#define DEBUG_BINARY_TREE 0
/*Binary tree data structure type*/
typedef struct node bt_node;

/**
 * @brief Create new node in the binary tree.
 * 
 * @param data Data value of the new node
 * @return Pointer to the new node
 */
bt_node* bt_new_nodes(int data);
/**
 * @brief Delete all nodes in binary tree
 * 
 * @param[in] node Pointer to binary tree 
 * @return none
 */
void bt_delete_tree(bt_node* node);
#endif