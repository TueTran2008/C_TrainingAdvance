#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "file_handle.h"
#include "morse_operation.h"
#include "binary_tree.h"

int main(int argc, char *argv[])
{
    int err = 0;
    size_t file_size = 0;
    int morse_operation = 0;

    if (argc < 4 || strcmp(argv[1], "--help") == 0)
    {
        printf("\r\n%s Morse operation on file: <Operation type> <Input file name> <Output filename>\r\n", argv[0]);
        printf("1 - Encoding: Text -> 1 Operation -> Morse code\r\n");
        printf("2 - Decodeing: Morse code -> 2 Operation -> Text\r\n");
        printf("Example: 1 input.txt output.txt\r\n");
        printf("The program only supports Alphabet uppercase\r\n");
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
    char *buf_out = (char*)malloc(file_size * 6);
    if (buf_rd == NULL)
    {
        printf("Unable to allocate memory\r\n");
        return 1;
    }
    file_handle_read(argv[2], buf_rd);
    if (morse_operation == MORSE_OPERATION_ENCODING)
    {
        err = morse_encode(buf_rd, buf_out, file_size);
        if(err)
        {
            printf("Error when encode\r\n");
            return 0;
        }
        file_handle_write(argv[3], buf_out);
    }
    else if (morse_operation == MORSE_OPERATION_DECODING)
    {
        err = morse_decode(buf_rd, buf_out, file_size);
        if(err)
        {
            printf("Error when decode\r\n");
            return 0;
        }
        file_handle_write(argv[3], buf_out);
    }
    if(err)
    {
        printf("Error while encode or decode -> Please check your input\r\n");    
    }
    free(buf_rd);
    morse_clean();
    return 0;
}

