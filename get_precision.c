#include "main.h"

/**
 * get_precision - it calculates the precision for printing
 * @format: Formatted string in which to print the arguments
 * @i: List of arguments to be printed
 * @list: list of arguments.
 *
 * Return: calculated Precision
 */
int get_precision(const char *format, int *i, va_list list)
{
	int c_i = *i + 1;
	int p = -1;

	if (format[c_i] != '.')
		return (p);

	p = 0;

	for (c_i += 1; format[c_i] != '\0'; c_i++)
	{
		if (is_digit(format[c_i]))
		{
			p *= 10;
			p += format[c_i] - '0';
		}
		else if (format[c_i] == '*')
		{
			c_i++;
			p = va_arg(list, int);
			break;
		}
		else
			break;
	}

	*i = c_i - 1;

	return (p);
}
