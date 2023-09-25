/******************************************************************************
 *                              HEADER AND DIRECTORY 
******************************************************************************/
#include "morse_code.h"
#include "binary_tree.h"
#include <stdio.h>
#include <string.h>
/******************************************************************************
 *                              DEFINE AND TYPEDEF 
******************************************************************************/
typedef struct morse_code
{
    /* data */
    char letter[5];
    char index;
}morse_encoded_string_t;
/******************************************************************************
 *                              PRIVATE VARIABLES
******************************************************************************/
static bt_node* m_root = NULL;
static morse_encoded_string_t m_encode_string;

/******************************************************************************
 *                              FORWARD DECLERATIONS
******************************************************************************/

/******************************************************************************
 *                              GLOBAL VARIALBE
******************************************************************************/

/******************************************************************************
 *                              PRIVATE FUNCTIONS
******************************************************************************/
static void create_morse_tree(void)
{
    /*root node*/
    if(m_root != NULL)
    {
        /*Already create node*/
        return;
    }
    printf("Initialize morse tree\r\n"
    );
    m_root = bt_new_nodes(' ');
    m_root->left = bt_new_nodes('E');
    m_root->left->left = bt_new_nodes('I');
    m_root->left->left->left = bt_new_nodes('S');
    m_root->left->left->left->left = bt_new_nodes('H');
    m_root->left->left->left->left->left = bt_new_nodes('5');
    m_root->left->left->left->left->right = bt_new_nodes('4');
    m_root->left->left->left->right = bt_new_nodes('V');
    m_root->left->left->left->right->right = bt_new_nodes('3');
    m_root->left->left->right = bt_new_nodes('U');
    m_root->left->left->right->right = bt_new_nodes(' ');
    m_root->left->left->right->right->right = bt_new_nodes('2');
    m_root->left->left->right->left = bt_new_nodes('F');

    m_root->left->right = bt_new_nodes('A');
    m_root->left->right->left = bt_new_nodes('R');
    m_root->left->right->left->left = bt_new_nodes('L');

    m_root->left->right->right = bt_new_nodes('W');
    m_root->left->right->right->left = bt_new_nodes('P');
    m_root->left->right->right->right = bt_new_nodes('J');
    m_root->left->right->right->right->right = bt_new_nodes('1');

    m_root->right = bt_new_nodes('T');
    m_root->right->left = bt_new_nodes('N');
    m_root->right->left->left = bt_new_nodes('D');
    m_root->right->left->left->left = bt_new_nodes('B');
    m_root->right->left->left->left->left = bt_new_nodes('6');
    m_root->right->left->left->left->right = bt_new_nodes('=');

    m_root->right->left->left->right = bt_new_nodes('X');
    m_root->right->left->left->right->left = bt_new_nodes('=');
    m_root->right->left->right = bt_new_nodes('K');
    m_root->right->left->right->left = bt_new_nodes('C');
    m_root->right->left->right->right = bt_new_nodes('Y');

    m_root->right->right = bt_new_nodes('M');
    m_root->right->right->left = bt_new_nodes('G');
    m_root->right->right->left->left = bt_new_nodes('Z');
    m_root->right->right->left->left = bt_new_nodes('7');

    m_root->right->right->left->right = bt_new_nodes('Q');


    m_root->right->right->right = bt_new_nodes('O');
    m_root->right->right->right->left = bt_new_nodes(' ');
    m_root->right->right->right->left->left = bt_new_nodes('8');

    //m_root->right->right->right->right->left = bt_new_nodes('9');
    //m_root->right->right->right->right->right = bt_new_nodes('@');
}
static bt_node* morse_search(bt_node *current, int key)
{
    if (current == NULL || current->data == key)
    {
        return NULL; 
    }
    printf("current data %c\r\n",current->data);
    if (current->data < key){
        m_encode_string.index += sprintf(m_encode_string.letter + m_encode_string.index, "%s", "-");
        return morse_search(current->right, key);
    }
    else
    {
        m_encode_string.index += sprintf(m_encode_string.letter + m_encode_string.index, "%s", "+");
        return morse_search(current->left, key);
    }
}

char* morse_encode_character(char key)
{
    m_encode_string.index = 0;
    memset(m_encode_string.letter, 0, sizeof(m_encode_string.letter));
    morse_search(m_root, key);
    return m_encode_string.letter;
}

void morse_decode_character(char* input, size_t input_size)
{

}


void morse_init(void)
{
    create_morse_tree();
    printf("Create tree done\r\n"
    );
    //bt_print_in_order(m_root);
}


