#include "main.h"
#include <stdarg.h>
#include <stdio.h>
#include <string.h>

/**
 * _printf - a function that produces output according to a format
 * @format: character string composed of zero or more directives
 *
 * Return: the number of characters printed (excluding the null byte)
 */
int _printf(const char *format, ...)
{
    va_list args;
    va_start(args, format);

    char buffer[1024] = {0};
    int count = 0;

    for (const char *traverse = format; *traverse != '\0'; traverse++)
    {
        while (*traverse != '%' && *traverse != '\0')
        {
            buffer[count++] = *traverse;
            traverse++;
        }

        if (*traverse == '\0')
            break;

        traverse++;

        // Handle flag characters
        int flag_plus = 0;
        int flag_space = 0;
        int flag_hash = 0;

        while (*traverse == '+' || *traverse == ' ' || *traverse == '#')
        {
            if (*traverse == '+') flag_plus = 1;
            if (*traverse == ' ') flag_space = 1;
            if (*traverse == '#') flag_hash = 1;
            traverse++;
        }

        switch (*traverse)
        {
            case 'd':
            case 'i':
            {
                int num = va_arg(args, int);
                char str[12]; // Buffer big enough for an int
                sprintf(str, "%d", num); // Convert the integer to a string

                // Handle '+' and ' ' flags
                if (num >= 0 && (flag_plus || flag_space))
                {
                    buffer[count++] = flag_plus ? '+' : ' ';
                }

                for (char *c = str; *c != '\0'; c++)
                {
                    buffer[count++] = *c;
                }
                break;
            }
            case 'o':
            case 'x':
            case 'X':
            {
                 unsigned int num = va_arg(args, unsigned int);
                 char str[9]; // Buffer big enough for an unsigned int in hexadecimal
                 sprintf(str, (*traverse == 'x') ? "%x" : ((*traverse == 'X') ? "%X" : "%o"), num); // Convert the integer to a string in hexadecimal

                 // Handle '#' flag
                 if (flag_hash && num != 0)
                 {
                     buffer[count++] = '0';
                     if (*traverse != 'o')
                     {
                         buffer[count++] = *traverse;
                     }
                 }

                 for (char *c = str; *c != '\0'; c++)
                 {
                     buffer[count++] = *c;
                 }
                 break;
             }
             // ... handle other conversion specifiers ...
        }
    }

    write(1, buffer, count);

    va_end(args);

    return count;
}

