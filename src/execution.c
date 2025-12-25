/*
** EPITECH PROJECT, 2024
** TCSH
** File description:
** execution.c
*/
#include "../include/shell.h"

int process_cmd(cmd_t *cmd, char **env)
{
    int i = access(cmd->argv[0], F_OK);
    pid_t pid;

    if (i != 0){
        return 0;
    } else {
        pid = fork();
        if (pid == 0){
            execve(cmd->argv[0], cmd->argv, env);
            exit(0);
        }
        wait(NULL);
    }
    return 1;
}

int my_exe(char *src, char **env, char **argv)
{
    pid_t pid = 0;
    int i = access(src, F_OK);

    if (errno == EACCES){
        write(2, src, my_strlen(src));
        write(2, ": Permission denied.", 21);
    }
    if (i == 0){
        pid = fork();
        if (pid == 0){
            execve(src, argv, env);
            exit(0);
        }
        wait(NULL);
    }
    if (i != 0){
        write(2, argv[0], my_strlen(argv[0]));
        write(2, ": Command not found.\n", 22);
        return 1;
    }
    return 0;
}

void handle_path(char **env, cmd_t *cmd)
{
    char **path = clean_path(env);
    pid_t pid = 0;
    char *str = NULL;
    path_state_t *state = malloc(sizeof(path_state_t));

    state->index = 0;
    state->path = path;
    for (int j = 0; path[state->index]; state->index++){
        str = my_strcat(path[state->index], cmd->argv[0]);
        j = access(str, F_OK);
        
        if (j == 0){
                pid = fork();
            if (pid == 0){
                execve(str, cmd->argv, env);
                exit(0);
            }
            wait(NULL);
            break;
        }
        if (!path[state->index + 1]) {
             write(2, cmd->argv[0], my_strlen(cmd->argv[0]));
             write(2, ": Command not found.\n", 21);
        }
    }
}

void move(shell_state_t *state, size_t size, int gl, cmd_t *cmd)
{
    if ((cmd->args[0] == 'c' && cmd->args[1] == 'd')
    || my_strcmp(cmd->args, "env") == 0
    || my_strcmp(cmd->args, "exit") == 0 || gl < 0
    || my_strcmp(cmd->args, "setenv") == 0
    || my_strcmp(cmd->args, "unsetenv") == 0
    || (cmd->args[0] == '.' && cmd->args[1] == '/')){
        my_functions(cmd, state, gl);
    } else if (my_strcmp(cmd->args, " ") != 0
    && my_strcmp(cmd->args, "\n") != 0
    && has_special_chars(cmd->args) != 1){
        handle_path(state->env, cmd);
    }
}

void execute_command(shell_state_t *state, size_t size, int gl, cmd_t *cmd)
{
    if (process_cmd(cmd, state->env) != 1){
        move(state, size, gl, cmd);
    }
}

// Pipe logic
void check_pid(pid_t pid)
{
    if (pid == -1){
        exit(EXIT_FAILURE);
    }
}

int handle_pipe(shell_state_t *state, size_t size, int gl, tree_node_t *node)
{
    int fd[2];
    pid_t pid;
    
    if (pipe(fd) == -1)
        exit(EXIT_FAILURE);
    pid = fork();
    check_pid(pid);
    if (pid == 0) {
        close(fd[0]);
        dup2(fd[1], STDOUT_FILENO);
        close(fd[1]);
        execute_command(state, size, gl, node->left);
        exit(0);
    } else {
        close(fd[1]);
        dup2(fd[0], STDIN_FILENO);
        close(fd[0]);
        execute_command(state, size, gl, node->right);
        wait(NULL);
    }
    return 0;
}

int execute_sequence(shell_state_t *state, size_t size, int gl, tree_node_t *node)
{
    execute_command(state, size, gl, node->left);
    execute_command(state, size, gl, node->right);
    wait(NULL);
    return 0;
}

int handle_separators(shell_state_t *state, size_t size, int gl, tree_node_t *node, char *args)
{
    if (has_pipe(args) == 2) {
        node = parse_separator(args);
        handle_pipe(state, size, gl, node);
    }
    if (has_semicolon(args) == 3){ 
        node = parse_separator(args);
        execute_sequence(state, size, gl, node);
    }
    return 0;
}
