/*
** EPITECH PROJECT, 2024
** B-PSU-200-COT-2-1-minishell1-kenzo.hounkpe
** File description:
** mini_printf
*/

#include "../include/shell.h"


static int lettre_specifique(char lettre, va_list ken)
{
    int c = 0;

    if (lettre == 'd' || lettre == 'i'){
        c += my_put_nbr(va_arg(ken, int));
    }
    if (lettre == 'c'){
        c += my_putchar(va_arg(ken, long));
    }
    if (lettre == 's'){
        c += my_putstr(va_arg(ken, char *));
    }
    if (lettre == '%'){
        c += my_putchar('%');
    }
    return (c);
}

int mini_printf(const char *format, ...)
{
    va_list ken;
    int c = 0;

    va_start(ken, format);
    for (; format[c] != '\0'; c++){
        if (format[c] == '%'){
            c++;
            lettre_specifique(format[c], ken);
        } else {
            my_putchar(format[c]);
        }
    }
    va_end(ken);
    return (c);
}
