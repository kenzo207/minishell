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

typedef struct shell_state_s {
    char **env;
    int last_exit_status;
} shell_state_t;

// --- utils.c ---
int my_strlen(char *str);
char *my_strcpy(char *dest, char const *str);
int my_strcmp(char *s1, char *s2);
int my_strncmp(char *s1, char *s2, int n);
char *my_strdup(char const *src);
void my_putchar(char c);
void my_putstr(char *str);
int mini_printf(char *str, ...);
char **my_str_to_word_array(char *str, char sep);

// --- prompt.c ---
void display_prompt(shell_state_t *state);
void display_simple_prompt(shell_state_t *state);

// --- aliases.c ---
char **apply_alias(char **argv);

// --- completion.c ---
void complete_input(char *buf, int *pos);
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
void my_functions(cmd_t *cmd, shell_state_t *state, int gl); // Updated to use shell_state
void display_help(void);

// --- parsing.c ---
char *clean_str(char *str);
char *my_clean(char *str);
int has_special_chars(char *args);
int has_pipe(char *args);
int has_semicolon(char *args);
cmd_t *parse_command(char *args, char **argv);
tree_node_t *parse_separator(char *args);

// --- tokenizer.c ---
typedef enum {
    TOKEN_WORD,
    TOKEN_PIPE,
    TOKEN_SEMICOLON,
    TOKEN_REDIR_OUT,
    TOKEN_REDIR_APPEND,
    TOKEN_REDIR_IN,
    TOKEN_HEREDOC,
    TOKEN_EOF
} token_type_t;

typedef struct token_s {
    token_type_t type;
    char *value;
    struct token_s *next;
} token_t;

token_t *create_token(token_type_t type, char *value);
void free_tokens(token_t *tokens);
token_t *tokenize(char *input);
void print_tokens(token_t *tokens);

// --- ast.c ---
typedef enum {
    AST_COMMAND,
    AST_PIPELINE,
    AST_SEQUENCE,
    AST_REDIRECT
} ast_node_type_t;

typedef enum {
    REDIR_OUTPUT,
    REDIR_APPEND,
    REDIR_INPUT,
    REDIR_HEREDOC
} redir_type_t;

typedef struct redir_s {
    redir_type_t type;
    char *target;
    struct redir_s *next;
} redir_t;

typedef struct ast_node_s {
    ast_node_type_t type;
    union {
        struct {
            char **argv;
            redir_t *redirs;
        } command;
        struct {
            struct ast_node_s *left;
            struct ast_node_s *right;
        } binary;
    } data;
} ast_node_t;

ast_node_t *create_command_node(char **argv, redir_t *redirs);
ast_node_t *create_binary_node(ast_node_type_t type, ast_node_t *left, ast_node_t *right);
redir_t *create_redir(redir_type_t type, char *target);
void free_redirs(redir_t *redirs);
void free_ast(ast_node_t *node);
ast_node_t *parse(token_t *tokens);
void print_ast(ast_node_t *node, int depth);

// --- ast_executor.c ---
int apply_redirections(redir_t *redirs);
int execute_ast_command(ast_node_t *node, shell_state_t *state);
int execute_ast_pipeline(ast_node_t *node, shell_state_t *state);
int execute_ast_sequence(ast_node_t *node, shell_state_t *state);
int execute_ast_node(ast_node_t *node, shell_state_t *state);

// --- execution.c ---
int process_cmd(cmd_t *cmd, char **env);
void handle_path(char **env, cmd_t *cmd);
int my_exe(char *src, char **env, char **argv);
void execute_command(shell_state_t *state, size_t size, int gl, cmd_t *cmd); // Updated
void move(shell_state_t *state, size_t size, int gl, cmd_t *cmd); // Updated
int handle_pipe(shell_state_t *state, size_t size, int gl, tree_node_t *node); // Updated
int handle_separators(shell_state_t *state, size_t size, int gl, tree_node_t *node, char *args); // Updated
int execute_sequence(shell_state_t *state, size_t size, int gl, tree_node_t *node); // Updated

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
