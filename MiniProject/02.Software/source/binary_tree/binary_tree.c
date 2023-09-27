/******************************************************************************
 *                              HEADER AND DIRECTORY 
******************************************************************************/
#include <stdlib.h>
#include "binary_tree.h"
#include <stdio.h>
#include <stdlib.h>
/******************************************************************************
 *                              DEFINE AND TYPEDEF 
******************************************************************************/
#if(DEBUG_BINARY_TREE)
#define DEBUG_BT(format_, ...)  printf(format_, ##__VA_ARGS__)
#else
#define DEBUG_BT(format_, ...) (void)(0)
#endif
/******************************************************************************
 *                              PRIVATE VARIABLES
******************************************************************************/

/******************************************************************************
 *                              FORWARD DECLERATIONS
******************************************************************************/

/******************************************************************************
 *                              GLOBAL VARIALBE
******************************************************************************/

/******************************************************************************
 *                              PRIVATE FUNCTIONS
******************************************************************************/
/******************************************************************************
 *                              GLOBAL FUNCTIONS
******************************************************************************/
bt_node* bt_new_nodes(int data)
{
    bt_node* node = (bt_node*)malloc(sizeof(bt_node));
    if(node == NULL)
    {
        DEBUG_BT("%s: Cannot create new node\r\n", __FUNCTION__);
        return NULL;
    }
    else
    {
        node->data = data;
        node->left = NULL;
        node->right = NULL;
        DEBUG_BT("Create node %c\r\n", data);
    }
    return node;
}
void bt_delete_tree(bt_node* node) 
{
    if (node == NULL) return;

    /* first delete both subtrees */
    bt_delete_tree(node->left);
    bt_delete_tree(node->right);
  
    /* then delete the node */
    DEBUG_BT("\n Deleting node: %d", node->data);
    free(node);
} 

 