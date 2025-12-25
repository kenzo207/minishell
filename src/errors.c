/*
** EPITECH PROJECT, 2024
** TCSH
** File description:
** errors.c
*/
#include "../include/shell.h"

int print_error(int k, char **argv, path_state_t *state, cmd_t *cmd)
{
    int j = 1;

    if (k != 0 && errno != ENOTDIR){
        write(2, argv[1], my_strlen(argv[1]));
        write(2, ": No such file or directory.\n", 29);
        return (0);
    }
    if (errno == ENOTDIR){
        write(2, argv[1], my_strlen(argv[1]));
        write(2, ": Not a directory.\n", 20);
        return (0);
    }
    if (j != 0 && !state->path[state->index + 1]){
        write(2, cmd->argv[0], my_strlen(cmd->argv[0]));
        write(2, ": Command not found.\n", 21);
        return (0);
    }
    return 0;
}
