#ifndef __MORSE_CODE_H__
#define __MORSE_CODE_H__
/******************************************************************************
 *                              HEADER AND DIRECTORY 
******************************************************************************/
#include <stdio.h>
/******************************************************************************
 *                              DEFINE AND TYPEDEF 
******************************************************************************/
typedef enum
{
    MORSE_OPERATION_INVALID = 0,
    MORSE_OPERATION_ENCODING = 1,
    MORSE_OPERATION_DECODING = 2,
    MORSE_OPERATION_MAX
}morse_operation_t;


#define DEBUG_MORSE_ENABLE 0
#define MORSE_SPACE_LENGTH_BETWEEN_LETTERS  1
#define MORSE_SPACE_LENGTH_BETWEEN_WORDS    7
/******************************************************************************
 *                              GLOBAL FUNCTIONS
******************************************************************************/
/**
 * @brief Reads the contents of a file into a string.
 *
 * @param[in] input Pointer to a buffer where the contents of the file will be stored.
 * @param[in] input_size Size of the input morse code string.
 * @return Charater value after decoded in ASCII. 
 *         Return - 1 if cannot find the value
 */
char morse_decode_character(char* input, size_t input_size);
/**
 * @brief Convert a character to a string of morse code.
 *
 * @param[in] key Input key value in character.
 * @param[in] p_out Pointer to the encoded string output.
 */
size_t morse_encode_character(char key, char* p_out);
/**
 * @brief Create the morse binary tree
 */
void morse_init(void);
/**
 * @brief Free the memory allocated by the morse binary tree
 */
void morse_clean(void);
#endif