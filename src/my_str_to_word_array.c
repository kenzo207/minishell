/*
** EPITECH PROJECT, 2023
** str to word array
** File description:
** str to word array
*/

#include <stdio.h>
#include <stdlib.h>
#include "../include/shell.h"

int sep_count(char *str, char sep)
{
    int i = 0;
    int a = 0;

    for (; str[i] != '\0'; i++){
        if (str[i] == sep){
            a++;
        }
    }
    return (a + 1);
}

int col_size(char *str, char sep)
{
    int i = 0;

    for (; str[i] != sep && str[i]; i++);
    return i;
}

char **my_str_to_word_array(char *str, char sep)
{
    int pres = 0;
    int str_i = 0;
    int col = col_size(str, sep);
    int j;
    int nb_sep = sep_count(str, sep);
    char **result = malloc(sizeof(char *) * (nb_sep +1));

    for (int a = 0; a < nb_sep; a++){
        col = col_size(&str[pres], sep);
        result[a] = malloc(col + 1);
        for (j = 0; j < col; j++){
            result[a][j] = str[str_i];
            str_i++;
        }
        result[a][j] = '\0';
        str_i++;
        pres = str_i;
    }
    result[nb_sep] = NULL;
    return result;
}
