/*
** EPITECH PROJECT, 2024
** TCSH
** File description:
** utils.c
*/
#include "../include/shell.h"

int my_strlen(char *str)
{
    int i = 0;
    while (str[i] != '\0') {
        i++;
    }
    return (i);
}

char *my_strcpy(char *dest, char const *str)
{
    int i = 0;
    while (str[i] != '\0') {
        dest[i] = str[i];
        i++;
    }
    dest[i] = '\0';
    return dest;
}

char *my_strcat(char *dest, char *src)
{
    int k = my_strlen(dest);
    int j = my_strlen(src);
    int o = k + j + 2;
    char *ret = malloc(sizeof(char) * o);
    int i;

    for (i = 0; dest[i] != '\0'; i++){
        ret[i] = dest[i];
    }
    ret[i] = '/';
    i++;
    for (int j = 0; src[j] != '\0'; j++){
        ret[i + j] = src[j];
    }
    ret[i + j] = '\0';
    return ret;
}

char *my_strdup(char *src)
{
    int i = my_strlen(src);
    char *dest = malloc(sizeof(char) * (i + 1));
    int nb = 0;

    for (; src[nb] != '\0'; nb++){
        dest[nb] = src[nb];
    }
    dest[nb] = '\0';
    return dest;
}

int my_strcmp(char *s1, char *s2)
{
    int i = 0;

    if (!s1 || !s2)
        return -1;
    while (s1[i] != '\0' && s2[i] != '\0') {
        if (s1[i] != s2[i])
            return (s1[i] - s2[i]);
        i++;
    }
    return (s1[i] - s2[i]);
}

int my_strncmp(char *s1, char *s2, int n)
{
    int i = 0;

    if (!s1 || !s2)
        return -1;
    while (i < n && s1[i] != '\0' && s2[i] != '\0') {
        if (s1[i] != s2[i])
            return (s1[i] - s2[i]);
        i++;
    }
    if (i < n)
        return (s1[i] - s2[i]);
    return 0;
}

int my_putchar(char c)
{
    write(1, &c, 1);
    return 0;
}

int my_putstr(char *str)
{
    write(1, str, my_strlen(str));
    return 0;
}

int my_put_nbr(int nb)
{
    int k;
    int j;

    if (nb < 0) {
        my_putchar('-');
        my_put_nbr(-nb);
    } else {
        j = (nb % 10);
        k = (nb / 10);
        if (k != 0)
            my_put_nbr(k);
        my_putchar(j + '0');
    }
    return 0;
}
