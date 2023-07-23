#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    char *buffer;
    size_t buffer_length;
    size_t input_length;
} input_buffer;

input_buffer* new_input_buffer()
{
    input_buffer* ibuffer = (input_buffer*) malloc(sizeof(input_buffer));
    ibuffer->buffer = NULL;
    ibuffer->buffer_length = 0;
    ibuffer->input_length = 0;

    return ibuffer;
}



void free_input_buffer(input_buffer* ibuffer)
{
    free(ibuffer->buffer);
    free(ibuffer);
}

void read_input(input_buffer* ibuffer)
{
    size_t bytes_read = getline(&(ibuffer->buffer), &(ibuffer->buffer_length), stdin);
    if (bytes_read <= 0)
    {
        fprintf(stderr, "Error reading input\n");
        exit(EXIT_FAILURE);
    }

    ibuffer->input_length = bytes_read - 1;
    ibuffer->buffer[bytes_read - 1] = 0;
}

typedef enum {
    META_COMMAND_SUCCESS,
    META_COMMAND_UNRECOGNIZED_COMMAND
} meta_command_result;


meta_command_result exec_meta_command(input_buffer* ibuffer)
{
    if (!strcmp(ibuffer->buffer, ".exit"))
    {
        free_input_buffer(ibuffer);
        exit(EXIT_SUCCESS);
    }

    return META_COMMAND_UNRECOGNIZED_COMMAND;
}

bool is_meta_command(input_buffer* ibuffer)
{
    return ibuffer->buffer[0] == '.';
}