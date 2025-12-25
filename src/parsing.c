/*
** EPITECH PROJECT, 2024
** TCSH
** File description:
** parsing.c
*/
#include "../include/shell.h"

char *clean_str(char *str)
{
    int j = 0;
    int o = 0;

    for (int i = 0; str[i]; i++){
        if ((str[i] != ' ') || (str[i - 1] != ' ')){
            str[j] = str[i];
            j++;
        }
    }
    for (int k = my_strlen(str); k > 0; k = k - 1){
        if ((str[k] == ' ') || (str[k - 1] == ' ')){
            str[k - 1] = '\0';
            str[o] = str[k - 1];
            o++;
        }
    }
    return str;
}

char **my_str_tok(char *str, char *sep)
{
    int i = 0;
    char **prog = malloc(sizeof(char *) * (my_strlen(str) + 1));
    char *token = strtok(str, sep);

    while (token) {
        prog[i] = token;
        token = strtok(NULL, sep);
        i++;
    }
    prog[i] = NULL;
    return prog;
}

char *my_clean(char *str)
{
    int i = 0;
    char *result;
    int j = 0;

    while (str[i] != '\0'){
        if (str[i] != ' ' && str[i] != '\n'){
            break;
        }
        i++;
    }
    result = my_strdup(&str[i]);
    while (result[j] != '\0'){
        if (result[j] == '\t'){
            result[j] = ' ';
            j++;
        }
        j++;
    }
    return result;
}

int has_special_chars(char *args)
{
    int i = 0;
    while (i < my_strlen(args)){
        if (args[i] == ' ' || args[i] == '\t' || args[i] == '\n'
        || args[i] == '/'){
            return 1;
        }
        i++;
    }
    return 0;
}

int has_pipe(char *args)
{
    int i = 0;
    while (i < my_strlen(args)) {
        if (args[i] == '|'){
            return 2;
        }
        i++;
    }
    return 0;
}

int has_semicolon(char *args)
{
    int i = 0;
    while (i < my_strlen(args)) {
        if (args[i] == ';'){
            return 3;
        }
        i++;
    }
    return 0;
}

cmd_t *parse_command(char *args, char **argv)
{
    cmd_t *cmd = malloc(sizeof(cmd_t));

    if (my_strcmp(args, " ") != 0 && my_strcmp(args, "\n") != 0){
        args = my_clean(args);
        argv = my_str_tok(args, " \t;");
    } else {
        args = "\0";
        argv = NULL;
    }
    cmd->args = args;
    cmd->argv = argv;
    return cmd;
}

tree_node_t *parse_separator(char *args)
{
    char **com = NULL;
    cmd_t *left_cmd;
    cmd_t *right_cmd;
    tree_node_t *node = malloc(sizeof(tree_node_t));
    char **argv1 = NULL;
    char **argv2 = NULL;

    for (int i = 0; args[i]; i++){
        if (args[i] == '|' || args[i] == ';'){
            com = my_str_tok(args, "|;");
            left_cmd = parse_command(com[0], argv1);
            right_cmd = parse_command(com[1], argv2);
        }
    }
    node->left = left_cmd;
    node->right = right_cmd;
    return node;
}
