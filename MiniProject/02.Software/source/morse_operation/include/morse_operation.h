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
 * @brief Encode a text string to Morse code and write to a file
 *
 * @param[in] input_string Pointer to data to be converte
 * @param[in] p_out Pointer to buffer holds encoded data
 * @param[in] string_len length of input text to be convert
 * @return 1 if encode fail
 *         0 if encode sucessfully
 */
int morse_encode(char* input_string, char *p_out, size_t string_len);
/**
 * @brief Decode a text string to Morse code and write to a file
 *
 * @param[in] input_string Pointer to data to be converte
 * @param[in] p_out Pointer to buffer holds encoded data
 * @param[in] string_len length of input text to be convert
 * @return 1 if decode fail
 *         0 if decode successfully
 */
int morse_decode(char* input_string, char* p_out, size_t string_len);
/**
 * @brief Create the morse binary tree
 */
void morse_init(void);
/**
 * @brief Free the memory allocated by the morse binary tree
 */
void morse_clean(void);
#endif