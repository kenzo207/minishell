/*
** EPITECH PROJECT, 2024
** TCSH
** File description:
** ast_executor.c - Execute AST nodes with redirection support
*/
#include "../include/shell.h"
#include <fcntl.h>

// Apply redirections for a command
int apply_redirections(redir_t *redirs)
{
    redir_t *current = redirs;
    
    while (current) {
        int fd;
        
        if (current->type == REDIR_OUTPUT) {
            // > output redirection
            fd = open(current->target, O_WRONLY | O_CREAT | O_TRUNC, 0644);
            if (fd < 0) {
                write(2, "mysh: ", 6);
                perror(current->target);
                return -1;
            }
            dup2(fd, STDOUT_FILENO);
            close(fd);
        }
        else if (current->type == REDIR_APPEND) {
            // >> append redirection
            fd = open(current->target, O_WRONLY | O_CREAT | O_APPEND, 0644);
            if (fd < 0) {
                write(2, "mysh: ", 6);
                perror(current->target);
                return -1;
            }
            dup2(fd, STDOUT_FILENO);
            close(fd);
        }
        else if (current->type == REDIR_INPUT) {
            // < input redirection
            fd = open(current->target, O_RDONLY);
            if (fd < 0) {
                write(2, "mysh: ", 6);
                perror(current->target);
                return -1;
            }
            dup2(fd, STDIN_FILENO);
            close(fd);
        }
        else if (current->type == REDIR_HEREDOC) {
            // << heredoc (simplified - just read until delimiter)
            // For now, we'll implement a basic version
            write(2, "mysh: heredoc not yet fully implemented\n", 41);
            return -1;
        }
        
        current = current->next;
    }
    
    return 0;
}

// Execute a simple command
int execute_ast_command(ast_node_t *node, shell_state_t *state)
{
    if (!node || node->type != AST_COMMAND)
        return -1;
    
    char **argv = node->data.command.argv;
    redir_t *redirs = node->data.command.redirs;
    
    if (!argv || !argv[0])
        return -1;
    
    // Check for builtins
    if (my_strcmp(argv[0], "cd") == 0 ||
        my_strcmp(argv[0], "env") == 0 ||
        my_strcmp(argv[0], "setenv") == 0 ||
        my_strcmp(argv[0], "unsetenv") == 0 ||
        my_strcmp(argv[0], "exit") == 0 ||
        my_strcmp(argv[0], "help") == 0) {
        
        // Create cmd_t for compatibility with existing builtins
        cmd_t cmd;
        cmd.args = argv[0];
        cmd.argv = argv;
        
        // Apply redirections before builtin execution
        if (redirs && apply_redirections(redirs) < 0)
            return -1;
        
        my_functions(&cmd, state, 0);
        return 0;
    }
    
    // External command - fork and execute
    pid_t pid = fork();
    if (pid < 0) {
        perror("fork");
        return -1;
    }
    
    if (pid == 0) {
        // Child process
        if (redirs && apply_redirections(redirs) < 0)
            exit(1);
        
        // Try to execute
        if (argv[0][0] == '/' || (argv[0][0] == '.' && argv[0][1] == '/')) {
            execve(argv[0], argv, state->env);
        } else {
            // Search in PATH
            char *path_env = get_path(state->env);
            if (path_env) {
                // Extract PATH value after "PATH="
                char *path_value = path_env + 5; // Skip "PATH="
                char **paths = my_str_to_word_array(path_value, ':');
                
                for (int i = 0; paths && paths[i]; i++) {
                    char full_path[1024];
                    snprintf(full_path, sizeof(full_path), "%s/%s", paths[i], argv[0]);
                    execve(full_path, argv, state->env);
                }
                
                // Free paths array
                for (int i = 0; paths && paths[i]; i++)
                    free(paths[i]);
                free(paths);
                free(path_env);
            }
        }
        
        // If we get here, command not found
        write(2, "mysh: ", 6);
        write(2, argv[0], my_strlen(argv[0]));
        write(2, ": Command not found\n", 20);
        exit(127);
    }
    
    // Parent process
    int status;
    waitpid(pid, &status, 0);
    if (WIFEXITED(status))
        state->last_exit_status = WEXITSTATUS(status);
    
    return 0;
}

// Execute pipeline
int execute_ast_pipeline(ast_node_t *node, shell_state_t *state)
{
    if (!node || node->type != AST_PIPELINE)
        return -1;
    
    int pipefd[2];
    if (pipe(pipefd) < 0) {
        perror("pipe");
        return -1;
    }
    
    pid_t pid1 = fork();
    if (pid1 < 0) {
        perror("fork");
        close(pipefd[0]);
        close(pipefd[1]);
        return -1;
    }
    
    if (pid1 == 0) {
        // First command - write to pipe
        close(pipefd[0]);
        dup2(pipefd[1], STDOUT_FILENO);
        close(pipefd[1]);
        
        execute_ast_node(node->data.binary.left, state);
        exit(state->last_exit_status);
    }
    
    pid_t pid2 = fork();
    if (pid2 < 0) {
        perror("fork");
        close(pipefd[0]);
        close(pipefd[1]);
        return -1;
    }
    
    if (pid2 == 0) {
        // Second command - read from pipe
        close(pipefd[1]);
        dup2(pipefd[0], STDIN_FILENO);
        close(pipefd[0]);
        
        execute_ast_node(node->data.binary.right, state);
        exit(state->last_exit_status);
    }
    
    // Parent - close pipe and wait
    close(pipefd[0]);
    close(pipefd[1]);
    
    int status;
    waitpid(pid1, &status, 0);
    waitpid(pid2, &status, 0);
    
    if (WIFEXITED(status))
        state->last_exit_status = WEXITSTATUS(status);
    
    return 0;
}

// Execute sequence
int execute_ast_sequence(ast_node_t *node, shell_state_t *state)
{
    if (!node || node->type != AST_SEQUENCE)
        return -1;
    
    execute_ast_node(node->data.binary.left, state);
    execute_ast_node(node->data.binary.right, state);
    
    return 0;
}

// Main AST executor
int execute_ast_node(ast_node_t *node, shell_state_t *state)
{
    if (!node)
        return -1;
    
    switch (node->type) {
        case AST_COMMAND:
            return execute_ast_command(node, state);
        case AST_PIPELINE:
            return execute_ast_pipeline(node, state);
        case AST_SEQUENCE:
            return execute_ast_sequence(node, state);
        default:
            return -1;
    }
}
