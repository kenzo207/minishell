#ifndef MY_H_
    #define MY_H_
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

typedef struct cmd_s {
    char *args;
    char **argv; // renamed from tab
} cmd_t;

typedef struct tree_node_s {
    cmd_t *left; // renamed from ken
    cmd_t *right; // renamed from len
    char *operator; // implicit based on usage, but keeping structure for now
} tree_node_t;

typedef struct path_state_s { // renamed from inu_t
    char **path;
    int index; // renamed from i
} path_state_t;

typedef struct exec_ctx_s { // renamed from mec_t
    tree_node_t *node; // renamed from ken
    char *args;
} exec_ctx_t;

int my_putchar(char c);
int my_put_nbr(int nb);
int my_putstr(char *str);

int mini_printf(const char *format, ...);
char *my_strcat(char *dest, char *src);
int sep_count(char *str, char sep);
int col_size(char *str, char sep);
char **my_str_to_word_array(char *str, char sep);
int my_strlen(char *str);
void disp_env(char **env);
void my_cd(char *src, char **env, char **argv);
char *my_strdup(char *src);
char *get_path(char **env);
char **clean_path(char **env);
void my_functions(cmd_t *cmd, char **env, int gl);
void handle_path(char **env, cmd_t *cmd); // typo fixed: hande_path -> handle_path
int my_strcmp(char *dest, char *src);
char *clean_str(char *str);
char *get_home(char **env);
char **my_str_tok(char *str, char *sep);
void my_execve(char *src, char **argv, char **env);
void my_setenv(char *str);
char *my_clean(char *str);
cmd_t *parse_command(char *args, char **argv); // renamed from conditions
int process_cmd(cmd_t *cmd, char **env); // renamed from proces
void move(char **env, size_t size, int gl, cmd_t *cmd);
int has_special_chars(char *args); // renamed from content
void execute_command(char **env, size_t size, int gl, cmd_t *cmd); // renamed from alli
void execute_logic(char **env, size_t size, int gl, cmd_t *cmd); // renamed from vig
cmd_t *parse_pipeline(char **env, size_t size, int gl, cmd_t *cmd); // renamed from cond2 (guessed purpose)
int handle_pipe(char **env, size_t size, int gl, tree_node_t *node); // renamed from npipe
int has_pipe(char *args); // renamed from con2
int check_errors(pid_t pid); // renamed from errors
void check_status(int status, int stop_sig); // renamed from errors2
int print_error(int k, char **argv, path_state_t *state, cmd_t *cmd); // renamed from err
int funt(void); // TODO: check usage
int funty(int i, size_t size, char *args, int gl); // TODO: check usage
int has_semicolon(char *args); // renamed from convg
int execute_sequence(char **env, size_t size, int gl, tree_node_t *node); // renamed from nvig
int handle_separators(char **env, size_t size, int gl, tree_node_t *node, char *args); // renamed from condi
tree_node_t *parse_separator(char *args); // renamed from concon

#endif
