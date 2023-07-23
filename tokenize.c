#include <stdlib.h>
#include <string.h>

#define TK_SPACE 32
#define TK_SELECT 448
#define TK_INSERT 469
#define TK_DELETE 435
#define TK_UPDATE 451

typedef struct {
    short int type;
    char* value;
} sql_token;

typedef struct {
    sql_token* tokens;
    size_t length;
} sql_token_collection;

sql_token_collection* new_sql_token_collection()
{
    sql_token_collection* token_collection = 
        (sql_token_collection*) malloc(sizeof(sql_token_collection));
    
    token_collection->tokens = NULL;
    token_collection->length = 0;

    return token_collection;
}

void free_sql_token_collection(sql_token_collection* token_collection)
{
    free(token_collection->tokens);
    free(token_collection);
}

void sql_token_collection_push(sql_token_collection* token_collection, sql_token token)
{
    token_collection->length++;

    size_t allocation_size = sizeof(sql_token) * token_collection->length;
    token_collection->tokens = realloc(token_collection->tokens, allocation_size);
    token_collection->tokens[token_collection->length-1] = token;
}

sql_token_collection* tokenize(char* sql_string)
{
    sql_token_collection* tokens = new_sql_token_collection();
    size_t sql_string_length = strlen(sql_string);

    int token_type = 0;
    char token_buffer[1024];
    int buffer_index = 0;

    for (int str_index = 0; str_index < sql_string_length; str_index++)
    {
        char c = *(sql_string + str_index);
        token_buffer[buffer_index++] = c;
        token_type += (int) c;
        
        if (*(sql_string + str_index + 1) == TK_SPACE || str_index+1 == sql_string_length)
        {
            token_buffer[buffer_index] = '\0';
            sql_token token;
            token.type = token_type;
            token.value = (char*) malloc(sizeof(char) * buffer_index);
            
            strcpy(token.value, token_buffer);
            memset(token_buffer, 0, buffer_index);
            buffer_index = 0;

            sql_token_collection_push(tokens, token);
            str_index++;
        }

        if (str_index+1 == sql_string_length) break;
    }

    return tokens;
}