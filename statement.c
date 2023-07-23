#include "stdio.h"
#include "./tokenize.c"
typedef enum {
    PREPARE_SUCCESS,
    PREPARE_UNRECOGNIZED_STATEMENT
} stmt_prepare_result;

typedef enum {
    STATEMENT_INSERT,
    STATEMENT_SELECT
} stmt_type;

typedef struct {
    stmt_type type;
} stmt;

stmt_prepare_result prepare_statement(char* buffer, stmt* statement)
{
    sql_token_collection* token_collection = tokenize(buffer);

    for (int i = 0; i < token_collection->length; i++)
    {
        printf(
            "[%d] [%s]\n", 
            token_collection->tokens[i].type,
            token_collection->tokens[i].value
        );
    }

    putchar('\n');
    free_sql_token_collection(token_collection);

    return PREPARE_SUCCESS;
}

void execute_statement(stmt *statement)
{
    switch (statement->type)
    {
        case STATEMENT_SELECT:
            puts("PERFORM SELECT");
            break;

        case STATEMENT_INSERT:
            puts("PERFORM INSERT");
            break;
    }
}