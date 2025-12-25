/*
** EPITECH PROJECT, 2024
** TCSH
** File description:
** completion.c - Tab auto-completion for files and directories
*/
#include "../include/shell.h"
#include <dirent.h>

// Get list of files matching prefix
char **get_completions(char *prefix, int *count)
{
    DIR *dir = opendir(".");
    struct dirent *entry;
    char **matches = malloc(sizeof(char *) * 256);
    int n = 0;
    
    if (!dir || !matches) {
        if (matches) free(matches);
        *count = 0;
        return NULL;
    }
    
    int prefix_len = my_strlen(prefix);
    
    while ((entry = readdir(dir)) != NULL) {
        // Skip . and ..
        if (my_strcmp(entry->d_name, ".") == 0 || 
            my_strcmp(entry->d_name, "..") == 0)
            continue;
        
        // Check if matches prefix
        if (prefix_len == 0 || my_strncmp(entry->d_name, prefix, prefix_len) == 0) {
            matches[n++] = my_strdup(entry->d_name);
            if (n >= 255) break;
        }
    }
    
    closedir(dir);
    matches[n] = NULL;
    *count = n;
    return matches;
}

// Find common prefix of all matches
char *find_common_prefix(char **matches, int count)
{
    if (count == 0) return my_strdup("");
    if (count == 1) return my_strdup(matches[0]);
    
    int len = 0;
    while (1) {
        char c = matches[0][len];
        if (c == '\0') break;
        
        for (int i = 1; i < count; i++) {
            if (matches[i][len] != c)
                goto done;
        }
        len++;
    }
    
done:
    char *prefix = malloc(len + 1);
    if (!prefix) return my_strdup("");
    
    for (int i = 0; i < len; i++)
        prefix[i] = matches[0][i];
    prefix[len] = '\0';
    
    return prefix;
}

// Complete the current input
void complete_input(char *buf, int *pos)
{
    int count = 0;
    char **matches = get_completions(buf, &count);
    
    if (count == 0) {
        // No match - beep
        write(1, "\a", 1);
        if (matches) free(matches);
        return;
    }
    
    if (count == 1) {
        // Single match - complete it
        int current_len = my_strlen(buf);
        int match_len = my_strlen(matches[0]);
        
        // Add the rest of the match
        for (int i = current_len; i < match_len && *pos < 1023; i++) {
            buf[(*pos)++] = matches[0][i];
            my_putchar(matches[0][i]);
        }
        
        // Add space after completion
        if (*pos < 1023) {
            buf[(*pos)++] = ' ';
            my_putchar(' ');
        }
    } else {
        // Multiple matches - show them
        char *common = find_common_prefix(matches, count);
        int current_len = my_strlen(buf);
        int common_len = my_strlen(common);
        
        // Complete to common prefix
        for (int i = current_len; i < common_len && *pos < 1023; i++) {
            buf[(*pos)++] = common[i];
            my_putchar(common[i]);
        }
        
        // Show all matches
        my_putchar('\n');
        for (int i = 0; i < count; i++) {
            my_putstr(matches[i]);
            my_putstr("  ");
            if ((i + 1) % 5 == 0) my_putchar('\n');
        }
        if (count % 5 != 0) my_putchar('\n');
        
        free(common);
    }
    
    // Free matches
    for (int i = 0; i < count; i++)
        free(matches[i]);
    free(matches);
}
