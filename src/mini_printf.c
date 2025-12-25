/*
** EPITECH PROJECT, 2024
** B-PSU-200-COT-2-1-minishell1-kenzo.hounkpe/*
** EPITECH PROJECT, 2024
** TCSH
** File description:
** mini_printf.c
*/
#include "../include/shell.h"
#include <stdarg.h>

int lettre_specifique(const char *format, va_list ken)
{
    int c = 0;
    if (*format == 'd' || *format == 'i'){
        c += my_put_nbr(va_arg(ken, int));
    }
    if (*format == 'c'){
        my_putchar(va_arg(ken, long));
        c++;
    }
    if (*format == 's'){
        char *str = va_arg(ken, char *);
        my_putstr(str);
        c += my_strlen(str);
    }
    if (*format == '%'){
        my_putchar('%');
        c++;
    }
    return c;
}

int mini_printf(char *format, ...)
{
    va_list ken;
    int i = 0;
    int c = 0;

    va_start(ken, format);
    while (format[i] != '\0'){
        if (format[i] == '%'){
            c += lettre_specifique(&format[i + 1], ken);
            i++;
        } else {
            my_putchar(format[i]);
            c++;
        }
        i++;
    }
    va_end(ken);
    return c;
}
