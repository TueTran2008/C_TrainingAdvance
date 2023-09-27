/******************************************************************************
 *                              HEADER AND DIRECTORY 
******************************************************************************/
#include "morse_operation.h"
#include "binary_tree.h"
#include <string.h>
#include <stdbool.h>
/******************************************************************************
 *                              DEFINE AND TYPEDEF 
******************************************************************************/
typedef struct morse_code
{
    /* data */
    char letter[5];
    char index;
}morse_encoded_string_t;

#if(DEBUG_MORSE_ENABLE)
#define DEBUG_MORSE(format_, ...)  printf(format_, ##__VA_ARGS__)
#else
#define DEBUG_MORSE(format_, ...) (void)(0)
#endif
/******************************************************************************
 *                              PRIVATE VARIABLES
******************************************************************************/
static bt_node* m_root = NULL;
static morse_encoded_string_t m_encode_string;
/******************************************************************************
 *                              FORWARD DECLERATIONS
******************************************************************************/
static void insert_morse_node(bt_node* root, char character, const char* morse_code);
static void create_morse_tree(void);
static bt_node* search_character(bt_node *current, char key);
/******************************************************************************
 *                              GLOBAL VARIALBE
******************************************************************************/

/******************************************************************************
 *                              PRIVATE FUNCTIONS
******************************************************************************/

/**
 * @brief Insert a note to morse binary tree
 *
 * @param[in] root Pointer to root node of binary tree
 * @param[in] character Value of the node
 * @param[in] morse_code Pointer to string contain Morse code appropriate with the character value
 */
static void insert_morse_node(bt_node* root, char character, const char* morse_code)
{
    bt_node* current = root;
    for (int i = 0; i < strlen(morse_code); i++) {
        if (morse_code[i] == '.') {
            if (current->left == NULL) {
                current->left = bt_new_nodes('\0'); // Null character represents internal node
            }
            current = current->left;
        } else if (morse_code[i] == '-') {
            if (current->right == NULL) {
                current->right = bt_new_nodes('\0'); // Null character represents internal node
            }
            current = current->right;
        }
    }
    current->data = character;
}

/**
 * @brief Create Morse Binary Tree Alphabet uppercase version
 */
static void create_morse_tree(void)
{
    /*root node*/
    if(m_root != NULL)
    {
        /*Already create node - Avoid call the init function again*/
        return;
    }
    DEBUG_MORSE("Initialize morse tree\r\n");
    m_root = bt_new_nodes('\0');
    insert_morse_node(m_root, 'A', ".-");
    insert_morse_node(m_root, 'B', "-...");
    insert_morse_node(m_root, 'C', "-.-.");
    insert_morse_node(m_root, 'D', "-..");
    insert_morse_node(m_root, 'E', ".");
    insert_morse_node(m_root, 'F', "..-.");
    insert_morse_node(m_root, 'G', "--.");
    insert_morse_node(m_root, 'H', "....");
    insert_morse_node(m_root, 'I', "..");
    insert_morse_node(m_root, 'J', ".---");
    insert_morse_node(m_root, 'K', "-.-");
    insert_morse_node(m_root, 'L', ".-..");
    insert_morse_node(m_root, 'M', "--");
    insert_morse_node(m_root, 'N', "-.");
    insert_morse_node(m_root, 'O', "---");
    insert_morse_node(m_root, 'P', ".--.");
    insert_morse_node(m_root, 'Q', "--.-");
    insert_morse_node(m_root, 'R', ".-.");
    insert_morse_node(m_root, 'S', "...");
    insert_morse_node(m_root, 'T', "-");
    insert_morse_node(m_root, 'U', "..-");
    insert_morse_node(m_root, 'V', "...-");
    insert_morse_node(m_root, 'W', ".--");
    insert_morse_node(m_root, 'X', "-..-");
    insert_morse_node(m_root, 'Y', "-.--");
    insert_morse_node(m_root, 'Z', "--..");
}
/**
 * @brief Search the character the Morse Alphabet binary tree 
 *
 * @param[in] current Pointer to node of binary tree
 * @param[in] key Value want to find
 * @return Pointer to next node has child contain the key value
 */
static bt_node* search_character(bt_node *current, char key)
{
    bt_node *next_node;
    if (current == NULL || current->data == key)
    {
        return current;
    }
    next_node = search_character(current->left, key);
    if (next_node != NULL)
    {
        return next_node;
    }
    next_node = search_character(current->right, key);
    if (next_node != NULL)
    {
        return next_node;
    }
    /*Cannot find the approriate character in this branch*/
    return NULL;
}

size_t morse_encode_character(char key, char *p_out)
{
    size_t size = 0;
    bt_node *current_node = m_root;
    while(current_node != NULL && current_node->data != key)
    {
        if (current_node->left != NULL && search_character(current_node->left, key) != NULL)
        {
            m_encode_string.index += sprintf(m_encode_string.letter + m_encode_string.index, "%s", ".");
            current_node = current_node->left;
        }
        else if (current_node->right != NULL && search_character(current_node->right, key) != NULL)
        {
            m_encode_string.index += sprintf(m_encode_string.letter + m_encode_string.index, "%s", "-");
            current_node = current_node->right;
        }
    }
    memcpy(p_out, m_encode_string.letter, m_encode_string.index);
    size = m_encode_string.index;
    /*Reset buffer*/
    m_encode_string.index = 0;
    memset(m_encode_string.letter, 0, sizeof(m_encode_string.letter));
    return size;
}

char morse_decode_character(char* input, size_t input_size)
{
    char ret_val = 0;
    bt_node *current_position = m_root;

    if (m_root == NULL)
    {
        DEBUG_MORSE("%s: Morse operation hasn't initialized yet\r\n", __FUNCTION__);
        return -1;
    }
    if (input == NULL || input_size == 0)
    {
        DEBUG_MORSE("%s: Invalid morse decode input\r\n", __FUNCTION__);
        return -1;
    }
    for (unsigned char i = 0; i < input_size; i++)
    {
        if(input[i] == '.')
        {
            current_position = current_position->left;
        }
        else if(input[i] == '-')
        {
            current_position = current_position->right;
        }
    }
    if (current_position == NULL)
    {
        DEBUG_MORSE("%s: Morse point to no where\r\n", __FUNCTION__);
        //return -1;
    }
    else
    {
        ret_val = current_position->data;
        DEBUG_MORSE("%s: Data:%c\r\n", __FUNCTION__, ret_val);
    }
    return ret_val;
}

void morse_init(void)
{
    create_morse_tree();
    DEBUG_MORSE("Create tree done\r\n");
}

void morse_clean(void)
{
    bt_delete_tree(m_root);
    m_root = NULL;
    DEBUG_MORSE("Release morse tree\r\n");
}


