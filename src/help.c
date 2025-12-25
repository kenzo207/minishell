/*
** EPITECH PROJECT, 2024
** TCSH
** File description:
** help.c
*/
#include "../include/shell.h"

void display_help(void)
{
    mini_printf("mysh - A TCSH-inspired shell\n\n");
    mini_printf("USAGE:\n");
    mini_printf("  ./mysh                  Start interactive shell\n");
    mini_printf("  echo \"cmd\" | ./mysh      Non-interactive mode\n\n");
    
    mini_printf("BUILT-IN COMMANDS:\n");
    mini_printf("  cd [dir]               Change directory\n");
    mini_printf("                         cd       - go to HOME\n");
    mini_printf("                         cd -     - go to previous directory\n");
    mini_printf("                         cd path  - go to path\n\n");
    
    mini_printf("  env                    Display environment variables\n\n");
    
    mini_printf("  setenv VAR [value]     Set environment variable\n");
    mini_printf("                         setenv       - display all variables\n");
    mini_printf("                         setenv VAR   - set VAR to empty string\n");
    mini_printf("                         setenv VAR value - set VAR to value\n\n");
    
    mini_printf("  unsetenv VAR           Remove environment variable\n\n");
    
    mini_printf("  exit [status]          Exit shell\n");
    mini_printf("                         exit     - exit with last status\n");
    mini_printf("                         exit N   - exit with status N\n\n");
    
    mini_printf("  help                   Display this help message\n\n");
    
    mini_printf("OPERATORS:\n");
    mini_printf("  |                      Pipe (connect commands)\n");
    mini_printf("  ;                      Sequence (run commands in order)\n\n");
    
    mini_printf("SPECIAL KEYS:\n");
    mini_printf("  Ctrl-D                 Exit shell (EOF)\n");
    mini_printf("  Backspace              Delete character\n\n");
    
    mini_printf("EXAMPLES:\n");
    mini_printf("  ls -la\n");
    mini_printf("  cd /tmp\n");
    mini_printf("  setenv MY_VAR hello\n");
    mini_printf("  ls | grep mysh\n");
    mini_printf("  echo hello ; ls\n\n");
}
