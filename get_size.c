#include "main.h"

/**
 * get_size - it calculates the size to cast the argument
 * @format: Formatted string in which to print the arguments
 * @i: List of arguments to be printed
 *
 * Return: calculated Precision
 */
int get_size(const char *format, int *i)
{
	int c_i = *i + 1;
	int x = 0;

	if (format[c_i] == 'l')
		x = S_LONG;
	else if (format[c_i] == 'h')
		x = S_SHORT;

	if (x == 0)
		*i = c_i - 1;
	else
		*i = c_i;

	return (x);
}
