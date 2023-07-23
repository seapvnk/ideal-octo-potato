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
    if (!strncmp(buffer, "insert", 6))
    {
        statement->type = STATEMENT_INSERT;
        return PREPARE_SUCCESS;
    }

    if (!strncmp(buffer, "select", 6))
    {
        statement->type = STATEMENT_SELECT;
        return PREPARE_SUCCESS;
    }

    return PREPARE_UNRECOGNIZED_STATEMENT;
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