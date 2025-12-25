/*
** EPITECH PROJECT, 2024
** TCSH
** File description:
** tokenizer.c - Robust tokenizer with quote and operator support
*/
#include "../include/shell.h"

// Token type definitions
typedef enum {
    TOKEN_WORD,
    TOKEN_PIPE,
    TOKEN_SEMICOLON,
    TOKEN_REDIR_OUT,      // >
    TOKEN_REDIR_APPEND,   // >>
    TOKEN_REDIR_IN,       // <
    TOKEN_HEREDOC,        // <<
    TOKEN_EOF
} token_type_t;

typedef struct token_s {
    token_type_t type;
    char *value;
    struct token_s *next;
} token_t;

// Create a new token
token_t *create_token(token_type_t type, char *value)
{
    token_t *token = malloc(sizeof(token_t));
    if (!token) {
        perror("malloc");
        return NULL;
    }
    token->type = type;
    token->value = value ? my_strdup(value) : NULL;
    token->next = NULL;
    return token;
}

// Free token list
void free_tokens(token_t *tokens)
{
    token_t *current = tokens;
    token_t *next;
    
    while (current) {
        next = current->next;
        if (current->value)
            free(current->value);
        free(current);
        current = next;
    }
}

// Check if character is a special operator
int is_operator_char(char c)
{
    return (c == '|' || c == ';' || c == '>' || c == '<');
}

// Skip whitespace
int skip_whitespace(char *str, int i)
{
    while (str[i] && (str[i] == ' ' || str[i] == '\t' || str[i] == '\n'))
        i++;
    return i;
}

// Extract word (handles quotes)
char *extract_word(char *str, int *i)
{
    int start = *i;
    int len = 0;
    char *word = malloc(1024); // Temporary buffer
    int in_single_quote = 0;
    int in_double_quote = 0;
    
    if (!word) {
        perror("malloc");
        return NULL;
    }
    
    while (str[*i]) {
        char c = str[*i];
        
        // Handle quotes
        if (c == '\'' && !in_double_quote) {
            in_single_quote = !in_single_quote;
            (*i)++;
            continue;
        }
        if (c == '"' && !in_single_quote) {
            in_double_quote = !in_double_quote;
            (*i)++;
            continue;
        }
        
        // If not in quotes, stop at whitespace or operators
        if (!in_single_quote && !in_double_quote) {
            if (c == ' ' || c == '\t' || c == '\n' || is_operator_char(c))
                break;
        }
        
        // Handle escape sequences (only outside single quotes)
        if (c == '\\' && !in_single_quote && str[*i + 1]) {
            (*i)++;
            word[len++] = str[*i];
            (*i)++;
            continue;
        }
        
        word[len++] = c;
        (*i)++;
    }
    
    word[len] = '\0';
    return word;
}

// Tokenize input string
token_t *tokenize(char *input)
{
    token_t *head = NULL;
    token_t *tail = NULL;
    int i = 0;
    
    if (!input)
        return NULL;
    
    while (input[i]) {
        token_t *token = NULL;
        
        // Skip whitespace
        i = skip_whitespace(input, i);
        if (!input[i])
            break;
        
        // Check for operators
        if (input[i] == '|') {
            token = create_token(TOKEN_PIPE, "|");
            i++;
        }
        else if (input[i] == ';') {
            token = create_token(TOKEN_SEMICOLON, ";");
            i++;
        }
        else if (input[i] == '>') {
            if (input[i + 1] == '>') {
                token = create_token(TOKEN_REDIR_APPEND, ">>");
                i += 2;
            } else {
                token = create_token(TOKEN_REDIR_OUT, ">");
                i++;
            }
        }
        else if (input[i] == '<') {
            if (input[i + 1] == '<') {
                token = create_token(TOKEN_HEREDOC, "<<");
                i += 2;
            } else {
                token = create_token(TOKEN_REDIR_IN, "<");
                i++;
            }
        }
        // Extract word
        else {
            char *word = extract_word(input, &i);
            if (word && word[0]) {
                token = create_token(TOKEN_WORD, word);
            }
            if (word)
                free(word);
        }
        
        // Add token to list
        if (token) {
            if (!head) {
                head = tail = token;
            } else {
                tail->next = token;
                tail = token;
            }
        }
    }
    
    return head;
}

// Debug: print tokens
void print_tokens(token_t *tokens)
{
    token_t *current = tokens;
    const char *type_names[] = {
        "WORD", "PIPE", "SEMICOLON", "REDIR_OUT", 
        "REDIR_APPEND", "REDIR_IN", "HEREDOC", "EOF"
    };
    
    while (current) {
        mini_printf("[%s: '%s'] ", type_names[current->type], 
                    current->value ? current->value : "");
        current = current->next;
    }
    mini_printf("\n");
}
