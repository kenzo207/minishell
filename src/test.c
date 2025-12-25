/*
** EPITECH PROJECT, 2024
** B-PSU-200-COT-2-1-minishell2-kenzo.hounkpe
** File description:
** test
*/
#include "../include/shell.h"
int funt(void)
{
    dup2(STDOUT_FILENO, 0);
    dup2(STDIN_FILENO, 1);
}

int funty(int i, size_t size, char *args, int gl)
{
    wait(&i);
    gl = getline(&args, &size, stdin);
}
