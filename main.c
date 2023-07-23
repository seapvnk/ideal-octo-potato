#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "./statement.c"
#include "./repl.c"

int main(int argc, char const *argv[])
{
    input_buffer* ibuffer = new_input_buffer();
    while (true)
    {
        printf("iop ~> ");
        read_input(ibuffer);

        if (is_meta_command(ibuffer))
        {
            if (exec_meta_command(ibuffer) == META_COMMAND_SUCCESS) continue;
            
            printf("Unrecognized command \"%s\"\n", ibuffer->buffer);
            continue;
        }

        stmt statement;
        if (prepare_statement(ibuffer->buffer, &statement) != PREPARE_SUCCESS)
        {
            printf("Unrecognized keyword at start of \"%s\"\n", ibuffer->buffer);
            continue;
        }

        execute_statement(&statement);
        puts("executed");
    }
    
    return 0;
}
