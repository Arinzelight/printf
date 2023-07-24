#include "main.h"
#include <stdio.h>

#define BUFF_SIZE 100

/************************* WRITE HANDLE *************************/
/**
* handle_write_char - Prints a character
* @c: char types.
* @buffer: Buffer array to handle print
* @flags:  Calculates active flags.
* @width: get width.
* @precision: precision specifier
* @size: Size specifier
*
* Return: Number of chars printed.
*/
int handle_write_char(char c, char buffer[],
int flags, int width, int precision, int size)
{
int i = 0;
char padd = ' ';

UNUSED(precision);
UNUSED(size);

if (flags & F_ZERO)
padd = '0';

buffer[i++] = c;
buffer[i] = '\0';

if (width > 1)
{
buffer[BUFF_SIZE - 1] = '\0';
for (i = 0; i < width - 1; i++)
buffer[BUFF_SIZE - i - 2] = padd;

if (flags & F_MINUS)
return (printf("%c%s", buffer[0], &buffer[BUFF_SIZE - i - 1]));
else
return (printf("%s%c", &buffer[BUFF_SIZE - i - 1], buffer[0]));
}
return (printf("%c", buffer[0]));
}
/************************* WRITE NUMBER *************************/
/**
* write_number - Prints a number
* @is_negative: List of arguments
* @ind: char types.
* @buffer: Buffer array to handle print
* @flags:  Calculates active flags
* @width: get width.
* @precision: precision specifier
* @size: Size specifier
*
* Return: Number of chars printed.
*/
int write_number(int is_negative, int ind, char buffer[],
int flags, int width, int precision, int size)
{
int length = BUFF_SIZE - ind - 1;
char padd = ' ', extra_ch = 0;
UNUSED(size);
if ((flags & F_ZERO) && !(flags & F_MINUS))
padd = '0';
if (is_negative)
extra_ch = '-';
else if (flags & F_PLUS)
extra_ch = '+';
else if (flags & F_SPACE)
extra_ch = ' ';
return (write_num(ind, buffer, flags, width, precision,
length, padd, extra_ch));
}
/**
* write_num - Write a number using a buffer
* @ind: Index at which the number starts on the buffer
* @buffer: Buffer
* @flags: Flags
* @width: width
* @prec: Precision specifier
* @length: Number length
* @padd: Padding char
* @extra_c: Extra char
*
* Return: Number of printed chars.
*/
int write_num(int ind, char buffer[], int flags, int width, int prec,
int length, char padd, char extra_c)
{
int i, padd_start = 1;

if (prec == 0 && ind == BUFF_SIZE - 2 && buffer[ind] == '0' && width == 0)
return (0); /* printf(".0d", 0)  no char is printed */
if (prec == 0 && ind == BUFF_SIZE - 2 && buffer[ind] == '0')
buffer[ind] = padd = ' '; /* width is displayed with padding ' ' */
if (prec > 0 && prec < length)
padd = ' ';
while (prec > length)
buffer[--ind] = '0', length++;
if (extra_c != 0)
length++;
if (width > length)
{
for (i = 1; i < width - length + 1; i++)
buffer[i] = padd;
buffer[i] = '\0';
if (flags & F_MINUS && padd == ' ')
{
if (extra_c)
buffer[--ind] = extra_c;
return (printf("%s%s", &buffer[ind], &buffer[1]));
}
else if (!(flags & F_MINUS) && padd == ' ')
{
if (extra_c)
buffer[--ind] = extra_c;
return (printf("%s%s", &buffer[1], &buffer[ind]));
}
else if (!(flags & F_MINUS) && padd == '0')
{
if (extra_c)
buffer[--padd_start] = extra_c;
return (printf("%s%s", &buffer[padd_start], &buffer[ind]));
}
}
if (extra_c)
buffer[--ind] = extra_c;
return (printf("%s", &buffer[ind]));
}
/**
* write_unsgnd - Writes an unsigned number
* @is_negative: Number indicating if the num is negative
* @ind: Index at which the number starts in the buffer
* @buffer: Array of chars
* @flags: Flags specifiers
* @width: Width specifier
* @precision: Precision specifier
* @size: Size specifier
*
* Return: Number of written chars.
*/
int write_unsgnd(int is_negative, int ind,
char buffer[],
int flags, int width, int precision, int size)
{
/* The number is stored at the buffer's right and starts at position i */
int length = BUFF_SIZE - ind - 1, i = 0;
char padd = ' ';

UNUSED(is_negative);
UNUSED(size);

if (precision == 0 && ind == BUFF_SIZE - 2 && buffer[ind] == '0')
return (0); /* printf(".0d", 0)  no char is printed */
if (precision > 0 && precision < length)
padd = ' ';
while (precision > length)
{
buffer[--ind] = '0';
length++;
}
if ((flags & F_ZERO) && !(flags & F_MINUS))
padd = '0';
if (width > length)
{
for (i = 0; i < width - length; i++)
buffer[i] = padd;

buffer[i] = '\0';

if (flags & F_MINUS) /* Asign extra char to the left of buffer [buffer>padd]*/
{
return (printf("%s%s", &buffer[ind], &buffer[0]));
}
else /* Asign extra char to the left of padding [padd>buffer]*/
{
return (printf("%s%s", &buffer[0], &buffer[ind]));
}
}

return (printf("%s", &buffer[ind]));
}
