#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "file_handle.h"
#include "morse_operation.h"
#include "binary_tree.h"

/**
 * @brief Encode a text string to Morse code and write to a file
 *
 * @param[in] input_string Pointer to data to be converte
 * @param[in] output_file Pointer to output directory
 * @param[in] string_len length of input text to be convert
 * @return 1 if encode fail
 *         0 if encode sucessfully
 */
static int encode(char* input_string, char *output_file, size_t string_len)
{
    char *rd_buf = (char*)malloc(string_len * 6);
    int len = 0;
    /*In case of encoding -> output length is bigger than the original ->about 6 time bigger*/
    for (unsigned int i = 0; i < string_len; i++)
    {
        input_string[i] = toupper(input_string[i]);
        if (input_string[i] >= 65 && input_string[i] <= 90) /*Upper letter case*/
        {
            len += morse_encode_character(input_string[i], rd_buf + len);
            len += sprintf(rd_buf + len, "%s", " "); /*Add a space between letter*/
        }
        else if (input_string[i] == ' ') /*Space case*/
        {
            len += sprintf(rd_buf + len, "%s", " / ");
        }
        else
        {
            printf("Character with hex value: 0x%02x - index: %d is not a value of Morse code uppercase Alphabet \r\n-> Please correct the input\r\n", input_string[i], i);
            return 1;
        }
    }
    file_handle_write(output_file, rd_buf);
    free(rd_buf);
    return 0;
}
/**
 * @brief Decode a text string to Morse code and write to a file
 *
 * @param[in] input_string Pointer to data to be converte
 * @param[in] output_file Pointer to output directory
 * @param[in] string_len length of input text to be convert
 * @return 1 if decode fail
 *         0 if decode successfully
 */
static int decode(char* input_string, char* output_file, size_t string_len)
{
    /*In case of decoding -> output length is smaller than the orignial ->*/
    char *rd_buf = (char*)malloc(string_len);
    char temp_buf[8];
    char temp_index = 0;
    int len = 0;
    bool is_space_between_letter = false;
    bool is_space_between_words = false;

    memset(temp_buf, 0, sizeof(temp_buf));
    /*Find the space*/
    for (unsigned int i = 0; i < string_len; i++)
    {
        if (input_string[i] == ' ') /*Detect space*/
        {
            if (i + 2 < string_len && input_string[i + 1] == '/' && input_string[i + 2] == ' ')
            {
                is_space_between_words = true;
                i = i + 2;
            }
            else
            {
                is_space_between_letter = true;
            }
        }
        else
        {
            temp_buf[temp_index++] = input_string[i];
            if(i == string_len - 1)
            {
                is_space_between_letter = true;
            }
        }
        if (is_space_between_words || is_space_between_letter)
        {
            char a = morse_decode_character(temp_buf, temp_index);
            if(a == -1)
            {
                printf("Cannot decode the value -> Input is not a Encoded Morse code");
                return 1;
            }
            temp_index = 0;
            memset(temp_buf, 0, sizeof(temp_buf));
            len += sprintf(rd_buf + len, "%c", a);
            if(is_space_between_words)
            {
                len += sprintf(rd_buf + len, " ");
            }
            is_space_between_words = false;
            is_space_between_letter = false;
        }
    }
    file_handle_write(output_file, rd_buf);
    free(rd_buf);
    return 0;
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
        err = encode(buf_rd, argv[3], file_size);
    }
    else if (morse_operation == MORSE_OPERATION_DECODING)
    {
        err = decode(buf_rd, argv[3], file_size);
    }
    if(err)
    {
        printf("Error while encode or decode -> Please check your input\r\n");    
    }
    free(buf_rd);
    morse_clean();
    return 0;
}

