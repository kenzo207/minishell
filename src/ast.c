/*
** EPITECH PROJECT, 2024
** TCSH
** File description:
** ast.c - Abstract Syntax Tree parser
*/
#include "../include/shell.h"

// Create command node
ast_node_t *create_command_node(char **argv, redir_t *redirs)
{
    ast_node_t *node = malloc(sizeof(ast_node_t));
    if (!node) {
        perror("malloc");
        return NULL;
    }
    
    node->type = AST_COMMAND;
    node->data.command.argv = argv;
    node->data.command.redirs = redirs;
    return node;
}

// Create binary node (pipeline or sequence)
ast_node_t *create_binary_node(ast_node_type_t type, ast_node_t *left, ast_node_t *right)
{
    ast_node_t *node = malloc(sizeof(ast_node_t));
    if (!node) {
        perror("malloc");
        return NULL;
    }
    
    node->type = type;
    node->data.binary.left = left;
    node->data.binary.right = right;
    return node;
}

// Create redirection node
redir_t *create_redir(redir_type_t type, char *target)
{
    redir_t *redir = malloc(sizeof(redir_t));
    if (!redir) {
        perror("malloc");
        return NULL;
    }
    
    redir->type = type;
    redir->target = my_strdup(target);
    redir->next = NULL;
    return redir;
}

// Free redirection list
void free_redirs(redir_t *redirs)
{
    redir_t *current = redirs;
    redir_t *next;
    
    while (current) {
        next = current->next;
        if (current->target)
            free(current->target);
        free(current);
        current = next;
    }
}

// Free AST
void free_ast(ast_node_t *node)
{
    if (!node) return;
    
    if (node->type == AST_COMMAND) {
        if (node->data.command.argv) {
            for (int i = 0; node->data.command.argv[i]; i++)
                free(node->data.command.argv[i]);
            free(node->data.command.argv);
        }
        free_redirs(node->data.command.redirs);
    } else {
        free_ast(node->data.binary.left);
        free_ast(node->data.binary.right);
    }
    
    free(node);
}

// Parse command from tokens (collect words and redirections)
ast_node_t *parse_command_tokens(token_t **tokens)
{
    char **argv = malloc(sizeof(char *) * 128);
    int argc = 0;
    redir_t *redirs = NULL;
    redir_t *last_redir = NULL;
    
    if (!argv) {
        perror("malloc");
        return NULL;
    }
    
    while (*tokens && (*tokens)->type != TOKEN_PIPE && (*tokens)->type != TOKEN_SEMICOLON) {
        token_t *tok = *tokens;
        
        // Handle redirections
        if (tok->type == TOKEN_REDIR_OUT || tok->type == TOKEN_REDIR_APPEND ||
            tok->type == TOKEN_REDIR_IN || tok->type == TOKEN_HEREDOC) {
            
            redir_type_t rtype;
            if (tok->type == TOKEN_REDIR_OUT) rtype = REDIR_OUTPUT;
            else if (tok->type == TOKEN_REDIR_APPEND) rtype = REDIR_APPEND;
            else if (tok->type == TOKEN_REDIR_IN) rtype = REDIR_INPUT;
            else rtype = REDIR_HEREDOC;
            
            *tokens = (*tokens)->next;
            if (!*tokens || (*tokens)->type != TOKEN_WORD) {
                write(2, "mysh: syntax error: expected filename after redirection\n", 57);
                free(argv);
                free_redirs(redirs);
                return NULL;
            }
            
            redir_t *new_redir = create_redir(rtype, (*tokens)->value);
            if (!redirs) {
                redirs = last_redir = new_redir;
            } else {
                last_redir->next = new_redir;
                last_redir = new_redir;
            }
        }
        // Handle words (command arguments)
        else if (tok->type == TOKEN_WORD) {
            argv[argc++] = my_strdup(tok->value);
        }
        
        *tokens = (*tokens)->next;
    }
    
    argv[argc] = NULL;
    
    if (argc == 0) {
        free(argv);
        free_redirs(redirs);
        return NULL;
    }
    
    return create_command_node(argv, redirs);
}

// Parse pipeline (cmd | cmd | cmd)
ast_node_t *parse_pipeline(token_t **tokens)
{
    ast_node_t *left = parse_command_tokens(tokens);
    if (!left) return NULL;
    
    while (*tokens && (*tokens)->type == TOKEN_PIPE) {
        *tokens = (*tokens)->next; // Skip pipe
        ast_node_t *right = parse_command_tokens(tokens);
        if (!right) {
            free_ast(left);
            return NULL;
        }
        left = create_binary_node(AST_PIPELINE, left, right);
    }
    
    return left;
}

// Parse sequence (cmd ; cmd ; cmd)
ast_node_t *parse_sequence(token_t **tokens)
{
    ast_node_t *left = parse_pipeline(tokens);
    if (!left) return NULL;
    
    while (*tokens && (*tokens)->type == TOKEN_SEMICOLON) {
        *tokens = (*tokens)->next; // Skip semicolon
        ast_node_t *right = parse_pipeline(tokens);
        if (!right) {
            free_ast(left);
            return NULL;
        }
        left = create_binary_node(AST_SEQUENCE, left, right);
    }
    
    return left;
}

// Main parser entry point
ast_node_t *parse(token_t *tokens)
{
    if (!tokens) return NULL;
    return parse_sequence(&tokens);
}

// Debug: print AST
void print_ast(ast_node_t *node, int depth)
{
    if (!node) return;
    
    for (int i = 0; i < depth; i++) mini_printf("  ");
    
    if (node->type == AST_COMMAND) {
        mini_printf("COMMAND: ");
        for (int i = 0; node->data.command.argv[i]; i++)
            mini_printf("%s ", node->data.command.argv[i]);
        mini_printf("\n");
        
        redir_t *r = node->data.command.redirs;
        while (r) {
            for (int i = 0; i < depth + 1; i++) mini_printf("  ");
            mini_printf("REDIR: %s %s\n", 
                r->type == REDIR_OUTPUT ? ">" :
                r->type == REDIR_APPEND ? ">>" :
                r->type == REDIR_INPUT ? "<" : "<<",
                r->target);
            r = r->next;
        }
    } else if (node->type == AST_PIPELINE) {
        mini_printf("PIPELINE\n");
        print_ast(node->data.binary.left, depth + 1);
        print_ast(node->data.binary.right, depth + 1);
    } else if (node->type == AST_SEQUENCE) {
        mini_printf("SEQUENCE\n");
        print_ast(node->data.binary.left, depth + 1);
        print_ast(node->data.binary.right, depth + 1);
    }
}
