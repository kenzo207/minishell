/*
** EPITECH PROJECT, 2024
** TCSH
** File description:
** builtins.c
*/
#include "../include/shell.h"

void disp_env(char **env)
{
    for (int i = 0; env[i]; i++){
        mini_printf("%s\n", env[i]);
    }
}

void my_cd(char *src, char **env, char **argv)
{
    int k = 0;
    char *str = get_home(env);
    char cwd[1024];
    char *oldpwd = NULL;
    
    // Get current directory for OLDPWD
    if (getcwd(cwd, sizeof(cwd)) == NULL) {
        perror("getcwd");
        if (str) free(str);
        return;
    }

    // cd with no arguments - go home
    if (argv[1] == NULL){
        if (str) {
            k = chdir(str);
            if (k == 0) {
                // Update OLDPWD
                setenv("OLDPWD", cwd, 1);
            }
        }
    }
    // cd - : go to previous directory
    else if (argv[1][0] == '-' && argv[1][1] == '\0'){
        oldpwd = getenv("OLDPWD");
        if (oldpwd) {
            k = chdir(oldpwd);
            if (k == 0) {
                // Don't print path - it messes up the prompt
                setenv("OLDPWD", cwd, 1);
            }
        } else {
            write(2, "mysh: cd: OLDPWD not set\n", 25);
        }
    }
    // cd <path>
    else if (argv[1][0] != '-'){
        k = chdir(argv[1]);
        if (k == 0) {
            setenv("OLDPWD", cwd, 1);
        }
    }
    
    // Handle errors
    if (k != 0){
        write(2, "mysh: cd: ", 10);
        if (argv[1]) {
            write(2, argv[1], my_strlen(argv[1]));
            write(2, ": ", 2);
        }
        if (errno == ENOTDIR) {
            write(2, "Not a directory\n", 16);
        } else if (errno == ENOENT) {
            write(2, "No such file or directory\n", 26);
        } else if (errno == EACCES) {
            write(2, "Permission denied\n", 18);
        } else {
            perror("");
        }
    }
    
    if (str) free(str);
}

// Builtin dispatcher - now takes shell_state
void my_functions(cmd_t *cmd, shell_state_t *state, int gl)
{
    // Check internal commands first
    if (my_strcmp(cmd->args, "env") == 0){
        disp_env(state->env);
    }
    else if (cmd->args[0] == 'c' && cmd->args[1] == 'd'){
        my_cd(cmd->args, state->env, cmd->argv);
    }
    else if ((cmd->args[0] == '.' && cmd->args[1] == '/')){
         if (access(cmd->args, X_OK) == 0){
            execve(cmd->args, cmd->argv, state->env);
         }
    }
    else if (cmd->args[0] == '/'){
        my_exe(cmd->args, state->env, cmd->argv);
    }
    else if (my_strcmp(cmd->args, "exit") == 0){
        // Support exit with status code
        int status = 0;
        if (cmd->argv[1]) {
            status = atoi(cmd->argv[1]);
        } else {
            status = state->last_exit_status;
        }
        mini_printf("exit\n");
        exit(status);
    }
    else if (my_strcmp(cmd->args, "setenv") == 0){
        if (!cmd->argv[1]){
            disp_env(state->env);
        } else {
            // setenv VAR value
            char *value = cmd->argv[2] ? cmd->argv[2] : "";
            my_setenv(cmd->argv[1]); // Validate name
            state->env = my_setenv_full(state->env, cmd->argv[1], value);
        }
    }
    else if (my_strcmp(cmd->args, "unsetenv") == 0){
        if (cmd->argv[1]){
            state->env = my_unsetenv(state->env, cmd->argv[1]);
        } else {
            write(2, "unsetenv: Too few arguments\n", 29);
        }
    }
    else if (my_strcmp(cmd->args, "help") == 0){
        display_help();
    }
}
