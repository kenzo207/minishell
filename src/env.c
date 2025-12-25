/*
** EPITECH PROJECT, 2024
** TCSH
** File description:
** env.c
*/
#include "../include/shell.h"

char *get_path(char **env)
{
    char *dest = NULL;
    for (int i = 0; env[i]; i++){
        if (env[i][0] == 'P' && env[i][1] == 'A'
        && env[i][2] == 'T' && env[i][3] == 'H'){
            dest = my_strdup(env[i]);
        }
    }
    return dest;
}

char **clean_path(char **env)
{
    char **path = NULL;
    char *src = get_path(env);
    if (!src) return NULL;
    path = my_str_tok(&src[5], ":");
    return path;
}

char *get_home(char **env)
{
    char *dest = NULL;
    for (int i = 0; env[i]; i++){
        if (env[i][0] == 'H' && env[i][1] == 'O'
        && env[i][2] == 'M' && env[i][3] == 'E'){
            dest = my_strdup(&env[i][5]);
        }
    }
    return dest;
}

void my_setenv(char *str)
{
    if ((str[0] < 'a' || str[0] > 'z') && str[0] != '_' && (str[0] < 'A'
    || str[0] > 'Z')){
        write(2, "setenv: Variable name must begin with a letter.\n", 49);
    }
    for (int i = 1; str[i] != '\0'; i++){
        if ((str[i] < 'a' || str[i] > 'z')
        && (str[i] < '0' || str[i] > '9') && str[i] != '_'
        && (str[i] < 'A' || str[i] > 'Z')){
            write(2, "setenv: Variable name must ", 28);
            write(2, "contain alphanumeric characters.\n", 34);
        }
    }
}
