/*
** EPITECH PROJECT, 2024
** TCSH
** File description:
** builtins.c
*/
#include "../include/shell.h"

void disp_env(char **env)
{
    char **env1 = NULL;
    for (int i = 0; env[i]; i++){
        mini_printf("%s\n", env[i]);
    }
}

void my_cd(char *src, char **env, char **argv)
{
    int k = 0;
    char *str = get_home(env);

    if (argv[1] == NULL){
        chdir(str);
    }
    if (argv[1] != NULL && argv[1][0] != '-'){
        k = chdir(argv[1]);
    }
    if (k != 0 && errno != ENOTDIR){
        write(2, argv[1], my_strlen(argv[1]));
        write(2, ": No such file or directory.\n", 29);
        return;
    }
}

void my_functions(cmd_t *cmd, char **env, int gl)
{
    // Check internal commands first
    if (my_strcmp(cmd->args, "env") == 0){
        disp_env(env);
    }
    else if (cmd->args[0] == 'c' && cmd->args[1] == 'd'){
        my_cd(cmd->args, env, cmd->argv);
    }
    else if ((cmd->args[0] == '.' && cmd->args[1] == '/')){
         if (access(cmd->args, X_OK) == 0){
            execve(cmd->args, cmd->argv, env);
        }
    }
    else if (cmd->args[0] == '/'){
        my_exe(cmd->args, env, cmd->argv);
    }
    else if (my_strcmp(cmd->args, "exit") == 0){
        mini_printf("exit\n");
        exit(0);
    }
    else if (my_strcmp(cmd->args, "setenv") == 0){
        if (!cmd->argv[1]){
            disp_env(env);
        } else {
            my_setenv(cmd->argv[1]);
        }
    }
}
