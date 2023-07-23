#include "main.h"

/* A FUNCTION THAT PRINTS POINTER */
/**
 * print_pointer - prints the value of a pointer variable
 * @types: List a of arguments
 * @buffer: Buffer array to handle print
 * @flags:  Calculates active flags
 * @width: get width
 * @precision: Precision specification
 * @size: Size specifier
 * Return: prints a number of chars
 */

int print_pointer(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	char extra = 0, pad = ' ';
	int dx = BUFF_SIZE - 2, length = 2, padd_start = 1; /* length=2, for '0x' */
	unsigned long num_addrs;
	char map_to[] = "0123456789abcdef";
	void *addrs = va_arg(types, void *);

	UNUSED(width);
	UNUSED(size);

	if (addrs == NULL)
		return (write(1, "(nil)", 5));

	buffer[BUFF_SIZE - 1] = '\0';
	UNUSED(precision);

	num_addrs = (unsigned long)addrs;

	while (num_addrs > 0)
	{
		buffer[dx--] = map_to[num_addrs % 16];
		num_addrs /= 16;
		length++;
	}

	if ((flags & F_ZERO) && !(flags & F_MINUS))
		pad = '0';
	if (flags & F_PLUS)
		extra = '+', length++;
	else if (flags & F_SPACE)
		extra = ' ', length++;

	dx++;

	/*return (write(1, &buffer[x], BUFF_SIZE - x - 1));*/
	return (write_pointer(buffer, dx, length,
		width, flags, pad, extra, padd_start));
}

/* PRINT A NON PRINTABLE */
/**
 * print_non_printable - Prints ascii codes in hexa of non printable chars
 * @types: Lista of arguments
 * @buffer: Buffer array to handle print
 * @flags:  Calculates active flags
 * @width: get width
 * @precision: Precision specification
 * @size: Size specifier
 * Return: Prints a number of chars
 */
int print_non_printable(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	int x = 0, os = 0;
	char *str = va_arg(types, char *);

	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);

	if (str == NULL)
		return (write(1, "(null)", 6));

	while (str[x] != '\0')
	{
		if (is_printable(str[x]))
			buffer[x + os] = str[x];
		else
			os += append_hexa_code(str[x], buffer, x + os);

		x++;
	}

	buffer[x + os] = '\0';

	return (write(1, buffer, x + os));
}

/*PRINT REVERSE FUNCTION */
/**
 * print_reverse - Prints an str in reverse
 * @types: Lista of arguments
 * @buffer: Buffer array to handle print
 * @flags:  Calculates active flags
 * @width: get width
 * @precision: Precision specification
 * @size: Size specifier
 * Return: prints a number of chars
 */

int print_reverse(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	char *str;
	int x, count = 0;

	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(size);

	str = va_arg(types, char *);

	if (str == NULL)
	{
		UNUSED(precision);

		str = ")Null(";
	}
	for (x = 0; str[x]; x++)
		;

	for (x = x - 1; x >= 0; x--)
	{
		char z = str[x];

		write(1, &z, 1);
		count++;
	}
	return (count);
}
/* PRINTS A STRING IN ROT13 */
/**
 * print_rot13string - Print a string in rot13.
 * @types: Lista of arguments
 * @buffer: Buffer array to handle print
 * @flags:  Calculates active flags
 * @width: get width
 * @precision: Precision specification
 * @size: Size specifier
 * Return: prints a number of chars
 */

int print_rot13string(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	char z;
	char *str;
	unsigned int x, j;
	int count = 0;
	char in[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
	char out[] = "NOPQRSTUVWXYZABCDEFGHIJKLMnopqrstuvwxyzabcdefghijklm";

	str = va_arg(types, char *);
	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);

	if (str == NULL)
		str = "(AHYY)";
	for (x = 0; str[x]; x++)
	{
		for (j = 0; in[j]; j++)
		{
			if (in[j] == str[x])
			{
				z = out[j];
				write(1, &z, 1);
				count++;
				break;
			}
		}
		if (!in[j])
		{
			z = str[x];
			write(1, &z, 1);
			count++;
		}
	}
	return (count);
}
