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
    // Wrap color codes to prevent cursor offset issues
    // Use write() to avoid mini_printf interpretation issues
    
    write(1, COLOR_BOLD, my_strlen(COLOR_BOLD));
    write(1, COLOR_GREEN, my_strlen(COLOR_GREEN));
    write(1, username, my_strlen(username));
    write(1, COLOR_RESET, my_strlen(COLOR_RESET));
    
    write(1, "@", 1);
    
    write(1, COLOR_BLUE, my_strlen(COLOR_BLUE));
    write(1, hostname, my_strlen(hostname));
    write(1, COLOR_RESET, my_strlen(COLOR_RESET));
    
    write(1, ":", 1);
    
    write(1, COLOR_CYAN, my_strlen(COLOR_CYAN));
    write(1, dir, my_strlen(dir));
    write(1, COLOR_RESET, my_strlen(COLOR_RESET));
    
    write(1, COLOR_YELLOW, my_strlen(COLOR_YELLOW));
    write(1, "$ ", 2);
    write(1, COLOR_RESET, my_strlen(COLOR_RESET));
}

// Simple prompt for non-colored terminals
void display_simple_prompt(shell_state_t *state)
{
    char *dir = get_current_dir(state->env);
    mini_printf("tcsh:%s$ ", dir);
}
