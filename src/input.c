/*
** EPITECH PROJECT, 2024
** TCSH
** File description:
** input.c
*/
#include "../include/shell.h"

static struct termios orig_termios;

void disable_raw_mode(void)
{
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &orig_termios);
}

void enable_raw_mode(void)
{
    struct termios raw;

    tcgetattr(STDIN_FILENO, &orig_termios);
    atexit(disable_raw_mode);
    raw = orig_termios;
    // Disable flags for raw mode
    raw.c_lflag &= ~(ECHO | ICANON | ISIG | IEXTEN); 
    // ECHO: disable echo
    // ICANON: disable canonical mode (read byte by byte)
    // ISIG: disable signals like Ctrl-C/Z (handling them manually later)
    // IEXTEN: disable Ctrl-V
    
    raw.c_iflag &= ~(BRKINT | ICRNL | INPCK | ISTRIP | IXON);
    // ICRNL: fix Ctrl-M vs Enter
    // IXON: disable Ctrl-S/Q
    
    raw.c_oflag &= ~(OPOST); // Disable output processing
    
    raw.c_cc[VMIN] = 0;
    raw.c_cc[VTIME] = 1;

    tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
}

char *read_command_line(void)
{
    char *buf = malloc(sizeof(char) * 1024); // simplistic buffer
    int i = 0;
    char c = 0;

    int nread;
    while (1) {
        nread = read(STDIN_FILENO, &c, 1);
        if (nread == -1 && errno != EAGAIN) {
             perror("read");
             exit(1);
        }
        if (nread == 0) continue; // Timeout or nothing read

        if (c == '\n' || c == '\r') {
             my_putchar('\n');
             break;
        } else if (c == 127) { // Backspace
            if (i > 0) {
                my_putstr("\b \b");
                i--;
            }
        } else if (c >= 32 && c < 127) {
            if (i < 1023) {
                buf[i++] = c;
                my_putchar(c);
            }
        }
        // TODO: Handle escape sequences for arrows
    }
    buf[i] = '\0';
    disable_raw_mode();
    return buf;
}
