#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "file_handle.h"
#include "morse_operation.h"
#include "binary_tree.h"

/**
 * @brief Encode a text string to Morse code and write to a file
 *
 * @param[in] input_string Pointer to data to be converte
 * @param[in] output_file Pointer to output directory
 * @param[in] string_len length of input text to be convert
 */
static void encode(char* input_string, char *output_file, size_t string_len)
{
    printf("File encode function\r\n");
    char *rd_buf = (char*)malloc(string_len * 6);
    int len = 0;
    /*In case of encoding -> output length is bigger than the original ->about 6 time bigger*/
    for (unsigned int i = 0; i < string_len; i++)
    {
        if (input_string[i] >= 65 && input_string[i] <= 90) /*Upper letter case*/
        {
            printf("%c\r\n", input_string[i]);
            len += morse_encode_character(input_string[i], rd_buf + len);
            len += sprintf(rd_buf + len, "%s", " "); /*Add a space between letter*/
        }
        else if (input_string[i] == ' ') /*Space case*/
        {
            len += sprintf(rd_buf + len, "%s", "   ");
        }
    }
    printf("DEbug RD_BUF: %s\r\n", rd_buf);
    file_handle_write(output_file, rd_buf);
    free(rd_buf);
}
/**
 * @brief Decode a text string to Morse code and write to a file
 *
 * @param[in] input_string Pointer to data to be converte
 * @param[in] output_file Pointer to output directory
 * @param[in] string_len length of input text to be convert
 */
static void decode(char* input_string, char* output_file, size_t string_len)
{
    /*In case of decoding -> output length is smaller than the orignial ->*/
    printf("File decode function\r\n");
    char *rd_buf = (char*)malloc(string_len);
    char temp_buf[8];
    char temp_index = 0;
    int len = 0;
    
    bool is_space_between_letter = false;
    bool is_space_between_words = false;
    //printf("File decode function\r\n");
    memset(temp_buf, 0, sizeof(temp_buf));
    /*Find the space*/
    for (unsigned int i = 0; i < string_len; i++)
    {
        temp_buf[temp_index++] = input_string[i];

        if (input_string[i] == ' ') /*Detect space*/
        {
            for (unsigned int j = i + MORSE_SPACE_LENGTH_BETWEEN_LETTERS; j < i + MORSE_SPACE_LENGTH_BETWEEN_WORDS; j++)
            {
                if (input_string[i] == 0)
                {
                    /*end*/
                    return;
                }
                else if (input_string[j] != ' ')
                {
                    is_space_between_letter = true;
                    break;
                }
            }
            if (is_space_between_letter == false)
            {
                is_space_between_words = true;
                i = i + MORSE_SPACE_LENGTH_BETWEEN_WORDS;
            }
        }
        if (is_space_between_words || is_space_between_letter)
        {
            char a = morse_decode_character(temp_buf, temp_index);
            temp_index = 0;
            memset(temp_buf, 0, sizeof(temp_buf));
            len += sprintf(rd_buf + len, "%c", a);
            if(is_space_between_words)
            {
                len = sprintf(rd_buf + len, " ");
            }
            is_space_between_words = 0;
            is_space_between_letter = 0;
        }
    }
    file_handle_write(output_file, rd_buf);
    free(rd_buf);
}

int main(int argc, char *argv[])
{
    int err = 0;
    size_t file_size = 0;
    int morse_operation = 0;

    if (argc < 4|| strcmp(argv[1], "--help") == 0)
    {
        printf("\r\n%s Morse operation on file: <Operation type> <Input file name> <Output filename>\r\n", argv[0]);
        printf("1 - Encoding: Text -> 1 Operation -> Morse code\r\n");
        printf("2 - Decodeing: Morse code -> 2 Operation -> Text\r\n");
        printf("Example: 1 input.txt output.txt\r\n");
        printf("The program only support Alphabet uppercase\r\n");
        return 0;
    }
    err = file_handle_check_file_exist(argv[2]);
    if (err == false)
    {
        printf("Input file not exist\r\n");
        return 0;
    }
    err = file_handle_is_valid_file_name(argv[3]);
    if (err == false)
    {
        printf("Output file name invalid\r\n");
        return 0;
    }
    morse_operation =  atoi(argv[1]);
    if (morse_operation != (int)MORSE_OPERATION_DECODING && morse_operation != (int)MORSE_OPERATION_ENCODING)
    {
        printf("Invalid input operation\r\n");
        return 0;
    }
    file_size = file_handle_get_file_size(argv[2]);
    if (file_size == 0)
    {
        printf("Empty input file\r\n");
        return 0;
    }
    printf("File size: %ld\r\n", file_size);
    morse_init();
    char *buf_rd = (char*)malloc(file_size * 2);
    if (buf_rd == NULL)
    {
        printf("Unable to allocate memory\r\n");
        return 1;
    }
    file_handle_read(argv[2], buf_rd);
    if (morse_operation == MORSE_OPERATION_ENCODING)
    {
        encode(buf_rd, argv[3], file_size);
    }
    else if (morse_operation == MORSE_OPERATION_DECODING)
    {
        decode(buf_rd, argv[3], file_size);
    }
    morse_clean();
    return 0;
}

