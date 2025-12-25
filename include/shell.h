/*
** EPITECH PROJECT, 2024
** TCSH
** File description:
** shell.h
*/

#ifndef SHELL_H_
    #define SHELL_H_
    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include <fcntl.h>
    #include <unistd.h>
    #include <stddef.h>
    #include <sys/stat.h>
    #include <sys/wait.h>
    #include <signal.h>
    #include <stdarg.h>
    #include <dirent.h>
    #include <errno.h>
    #include <termios.h>

typedef struct cmd_s {
    char *args;
    char **argv;
} cmd_t;

typedef struct tree_node_s {
    cmd_t *left;
    cmd_t *right;
    char *operator;
} tree_node_t;

typedef struct path_state_s {
    char **path;
    int index;
} path_state_t;

// --- utils.c ---
int my_strlen(char *str);
char *my_strcpy(char *dest, char const *str);
char *my_strcat(char *dest, char *src);
char *my_strdup(char *src);
int my_strcmp(char *dest, char *src);
int my_putchar(char c);
int my_put_nbr(int nb);
int my_putstr(char *str);
int mini_printf(const char *format, ...);
char **my_str_to_word_array(char *str, char sep);
char **my_str_tok(char *str, char *sep);

// --- env.c ---
void disp_env(char **env);
char *get_path(char **env);
char **clean_path(char **env);
char *get_home(char **env);
void my_setenv(char *str);
int count_env(char **env);
char **copy_env(char **env);
int find_env_var(char **env, char *name);
char **my_setenv_full(char **env, char *name, char *value);
char **my_unsetenv(char **env, char *name);

// --- builtins.c ---
void my_cd(char *src, char **env, char **argv);
void my_functions(cmd_t *cmd, char **env, int gl); // Dispatcher

// --- parsing.c ---
char *clean_str(char *str);
char *my_clean(char *str);
int has_special_chars(char *args);
int has_pipe(char *args);
int has_semicolon(char *args);
cmd_t *parse_command(char *args, char **argv);
tree_node_t *parse_separator(char *args);

// --- execution.c ---
int process_cmd(cmd_t *cmd, char **env);
void handle_path(char **env, cmd_t *cmd);
int my_exe(char *src, char **env, char **argv);
void execute_command(char **env, size_t size, int gl, cmd_t *cmd);
void move(char **env, size_t size, int gl, cmd_t *cmd);
int handle_pipe(char **env, size_t size, int gl, tree_node_t *node);
int handle_separators(char **env, size_t size, int gl, tree_node_t *node, char *args);
int execute_sequence(char **env, size_t size, int gl, tree_node_t *node);

// --- errors.c ---
int print_error(int k, char **argv, path_state_t *state, cmd_t *cmd);
void check_pid(pid_t pid); // was myl

// --- input.c ---
char *read_command_line(void);
// unused or TODO
int funt(void); 
int funty(int i, size_t size, char *args, int gl);
int sep_count(char *str, char sep); // in my_str_to_word_array
int col_size(char *str, char sep); // in my_str_to_word_array

#endif
