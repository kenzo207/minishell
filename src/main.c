/*
** EPITECH PROJECT, 2024
** TCSH
** File description:**
** main.c
*/
#include "../include/shell.h"

void my_shell(char **av, shell_state_t *state)
{
    char *args = NULL;
    int gl = 0;

    while (1){
        if (isatty(STDIN_FILENO))
            display_prompt(state);  // Beautiful colored prompt
        
        args = read_command_line(state);
        if (args == NULL) break;
        
        gl = my_strlen(args);
        if (gl == 0 || (args[0] == '\n')) {
            free(args);
            continue;
        }
        
        // New AST-based execution
        token_t *tokens = tokenize(args);
        if (tokens) {
            ast_node_t *ast = parse(tokens);
            if (ast) {
                execute_ast_node(ast, state);
                free_ast(ast);
            }
            free_tokens(tokens);
        }
        
        free(args);
    }
}

int main(int ac, char **av, char **env)
{
    shell_state_t state;
    
    // Copy environment to make it mutable
    state.env = copy_env(env);
    if (!state.env) {
        write(2, "mysh: failed to copy environment\n", 34);
        return 1;
    }
    state.last_exit_status = 0;
    
    my_shell(av, &state);
    
    // Free environment copy
    for (int i = 0; state.env[i]; i++)
        free(state.env[i]);
    free(state.env);
    
    return state.last_exit_status;
}
