/*
** EPITECH PROJECT, 2024
** TCSH
** File description:
** prompt.c - Beautiful colored prompt with current directory
*/
#include "../include/shell.h"
#include <pwd.h>

// ANSI color codes
#define COLOR_RESET   "\033[0m"
#define COLOR_BOLD    "\033[1m"
#define COLOR_GREEN   "\033[32m"
#define COLOR_BLUE    "\033[34m"
#define COLOR_CYAN    "\033[36m"
#define COLOR_YELLOW  "\033[33m"

// Get username
char *get_username(void)
{
    struct passwd *pw = getpwuid(getuid());
    if (pw)
        return pw->pw_name;
    return "user";
}

// Get hostname
char *get_hostname(void)
{
    static char hostname[256];
    if (gethostname(hostname, sizeof(hostname)) == 0)
        return hostname;
    return "localhost";
}

// Get current directory (shortened if in HOME)
char *get_current_dir(char **env)
{
    static char cwd[1024];
    char *home = get_home(env);
    
    if (getcwd(cwd, sizeof(cwd)) == NULL) {
        if (home) free(home);
        return "~";
    }
    
    // Replace HOME with ~
    if (home) {
        int home_len = my_strlen(home);
        if (my_strncmp(cwd, home, home_len) == 0) {
            static char short_cwd[1024];
            short_cwd[0] = '~';
            my_strcpy(short_cwd + 1, cwd + home_len);
            free(home);
            return short_cwd;
        }
        free(home);
    }
    
    return cwd;
}

// Display beautiful colored prompt
void display_prompt(shell_state_t *state)
{
    char *username = get_username();
    char *hostname = get_hostname();
    char *dir = get_current_dir(state->env);
    
    // Format: [user@host:dir]$ 
    // With colors: [GREEN]user[RESET]@[BLUE]host[RESET]:[CYAN]dir[RESET][YELLOW]$[RESET]
    mini_printf("%s%s%s@%s%s%s:%s%s%s%s$ %s",
        COLOR_BOLD, COLOR_GREEN, username,
        COLOR_BLUE, hostname,
        COLOR_RESET,
        COLOR_CYAN, dir,
        COLOR_RESET,
        COLOR_YELLOW,
        COLOR_RESET);
}

// Simple prompt for non-colored terminals
void display_simple_prompt(shell_state_t *state)
{
    char *dir = get_current_dir(state->env);
    mini_printf("tcsh:%s$ ", dir);
}
