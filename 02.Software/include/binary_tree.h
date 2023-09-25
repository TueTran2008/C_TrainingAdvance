#ifndef __BINARY_TREE_H__
#define __BINARY_TREE_H__
typedef struct node bt_node;
struct node {
    int data;
    bt_node* left;
    bt_node* right;
};
/*Binary tree data structure type*/
typedef struct node bt_node;

/**
 * @brief Create new node in the binary tree.
 * 
 * @param data Data value of the new node
 * @return Pointer to the new node
 */
bt_node* bt_new_nodes(int data);


void bt_print_in_order(bt_node* node);
#endif