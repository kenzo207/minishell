/*
** EPITECH PROJECT, 2024
** TCSH
** File description:**
** main.c
*/
#include "../include/shell.h"

void my_shell(char **av, shell_state_t *state)
{
    size_t size = 0;
    char *args = NULL;
    int gl = 0;
    char **tab = NULL;
    int i = 0;
    cmd_t *cmd;
    tree_node_t *node;

    while (gl != -1){
        if (isatty(STDIN_FILENO))
            mini_printf("tcsh$> ");
        args = read_command_line();
        if (args == NULL) break;
        
        gl = my_strlen(args); 

        if (has_pipe(args) != 2 && has_semicolon(args) != 3){
            cmd = parse_command(args, tab);
            execute_command(state->env, size, gl, cmd);
        } else {
             handle_separators(state->env, size, gl, node, args); 
        }
        wait(&i);
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
