/*
** EPITECH PROJECT, 2024
** TCSH
** File description:
** main.c
*/
#include "../include/shell.h"

void my_shell(char **av, char **env)
{
    size_t size = 0;
    char *args = NULL;
    int gl = 0;
    char **tab = NULL;
    int i = 0;
    cmd_t *cmd;
    tree_node_t *node;

    while (gl != -1){
        mini_printf("tcsh$> ");
        args = read_command_line();
        if (args == NULL) break;
        
        gl = my_strlen(args); 
        // Emulate getline return length slightly for logic continuity, 
        // but existing logic just checked gl != -1. 
        // We will make read_command_line return NULL on EOF/Ctrl-D.

        if (has_pipe(args) != 2 && has_semicolon(args) != 3){
            cmd = parse_command(args, tab);
            execute_command(env, size, gl, cmd);
        } else {
             handle_separators(env, size, gl, node, args); 
        }
        wait(&i);
    }
}

int main(int ac, char **av, char **env)
{
    my_shell(av, env);
    return 0;
}
