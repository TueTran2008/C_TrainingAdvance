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

#define DEBUG_ENABLE 1
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
void bt_print_in_order(bt_node* node)
{
    if (node == NULL)
        return;
    // First recur on left child
    bt_print_in_order(node->left);
    // Then print the data of node
    printf("%d ", node->data);
    // Now recur on right child
    bt_print_in_order(node->right);
}
/******************************************************************************
 *                              GLOBAL FUNCTIONS
******************************************************************************/
bt_node* bt_new_nodes(int data)
{
    bt_node* node = (bt_node*)malloc(sizeof(bt_node));
    if(node == NULL)
    {
        printf("%s: Cannot create new node\r\n", __FUNCTION__);
        return NULL;
    }
    else
    {
        node->data = data;
        node->left = NULL;
        node->right = NULL;
        printf("Create node %c\r\n", data);
    }
    return node;
}

 