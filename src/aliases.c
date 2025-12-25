/*
** EPITECH PROJECT, 2024
** TCSH
** File description:
** aliases.c - Command aliases for better UX
*/
#include "../include/shell.h"

// Check if command should be aliased
char **apply_alias(char **argv)
{
    if (!argv || !argv[0])
        return argv;
    
    // ls -> ls --color=auto
    if (my_strcmp(argv[0], "ls") == 0) {
        // Count existing args
        int count = 0;
        while (argv[count])
            count++;
        
        // Check if --color is already present
        for (int i = 1; i < count; i++) {
            if (my_strcmp(argv[i], "--color") == 0 || 
                my_strcmp(argv[i], "--color=auto") == 0 ||
                my_strcmp(argv[i], "--color=always") == 0)
                return argv; // Already has color option
        }
        
        // Create new argv with --color=auto
        char **new_argv = malloc(sizeof(char *) * (count + 2));
        if (!new_argv)
            return argv;
        
        new_argv[0] = my_strdup("ls");
        new_argv[1] = my_strdup("--color=auto");
        for (int i = 1; i < count; i++)
            new_argv[i + 1] = my_strdup(argv[i]);
        new_argv[count + 1] = NULL;
        
        // Free old argv
        for (int i = 0; argv[i]; i++)
            free(argv[i]);
        free(argv);
        
        return new_argv;
    }
    
    return argv;
}
