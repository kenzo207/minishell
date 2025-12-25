/*
** EPITECH PROJECT, 2024
** TCSH
** File description:
** env.c
*/
#include "../include/shell.h"

char *get_path(char **env)
{
    char *dest = NULL;
    for (int i = 0; env[i]; i++){
        if (env[i][0] == 'P' && env[i][1] == 'A'
        && env[i][2] == 'T' && env[i][3] == 'H'){
            dest = my_strdup(env[i]);
        }
    }
    return dest;
}

char **clean_path(char **env)
{
    char **path = NULL;
    char *src = get_path(env);
    if (!src) return NULL;
    path = my_str_tok(&src[5], ":");
    return path;
}

char *get_home(char **env)
{
    char *dest = NULL;
    for (int i = 0; env[i]; i++){
        if (env[i][0] == 'H' && env[i][1] == 'O'
        && env[i][2] == 'M' && env[i][3] == 'E'){
            dest = my_strdup(&env[i][5]);
        }
    }
    return dest;
}

void my_setenv(char *str)
{
    if ((str[0] < 'a' || str[0] > 'z') && str[0] != '_' && (str[0] < 'A'
    || str[0] > 'Z')){
        write(2, "setenv: Variable name must begin with a letter.\n", 49);
    }
    for (int i = 1; str[i] != '\0'; i++){
        if ((str[i] < 'a' || str[i] > 'z')
        && (str[i] < '0' || str[i] > '9') && str[i] != '_'
        && (str[i] < 'A' || str[i] > 'Z')){
            write(2, "setenv: Variable name must ", 28);
            write(2, "contain alphanumeric characters.\n", 34);
        }
    }
}

// Count environment variables
int count_env(char **env)
{
    int count = 0;
    if (!env) return 0;
    while (env[count])
        count++;
    return count;
}

// Copy environment to make it mutable
char **copy_env(char **env)
{
    int count = count_env(env);
    char **new_env = malloc(sizeof(char *) * (count + 1));
    
    if (!new_env) {
        perror("malloc");
        return NULL;
    }
    
    for (int i = 0; i < count; i++) {
        new_env[i] = my_strdup(env[i]);
        if (!new_env[i]) {
            // Free previously allocated strings on error
            for (int j = 0; j < i; j++)
                free(new_env[j]);
            free(new_env);
            return NULL;
        }
    }
    new_env[count] = NULL;
    return new_env;
}

// Find environment variable by name, return index or -1
int find_env_var(char **env, char *name)
{
    if (!env || !name) return -1;
    
    int name_len = my_strlen(name);
    for (int i = 0; env[i]; i++) {
        if (my_strlen(env[i]) >= name_len + 1 &&
            env[i][name_len] == '=' &&
            strncmp(env[i], name, name_len) == 0) {
            return i;
        }
    }
    return -1;
}

// Set environment variable (name=value), returns new env
char **my_setenv_full(char **env, char *name, char *value)
{
    if (!name || !value) return env;
    
    int idx = find_env_var(env, name);
    char *new_var = malloc(my_strlen(name) + my_strlen(value) + 2);
    
    if (!new_var) {
        perror("malloc");
        return env;
    }
    
    my_strcpy(new_var, name);
    my_strcat(new_var, "=");
    my_strcat(new_var, value);
    
    if (idx >= 0) {
        // Variable exists, replace it
        free(env[idx]);
        env[idx] = new_var;
    } else {
        // Variable doesn't exist, add it
        int count = count_env(env);
        char **new_env = malloc(sizeof(char *) * (count + 2));
        
        if (!new_env) {
            perror("malloc");
            free(new_var);
            return env;
        }
        
        for (int i = 0; i < count; i++)
            new_env[i] = env[i];
        new_env[count] = new_var;
        new_env[count + 1] = NULL;
        free(env);
        env = new_env;
    }
    
    return env;
}

// Unset environment variable, returns new env
char **my_unsetenv(char **env, char *name)
{
    if (!name) return env;
    
    int idx = find_env_var(env, name);
    if (idx < 0) return env; // Variable doesn't exist
    
    free(env[idx]);
    
    // Shift remaining variables down
    for (int i = idx; env[i]; i++) {
        env[i] = env[i + 1];
    }
    
    return env;
}

