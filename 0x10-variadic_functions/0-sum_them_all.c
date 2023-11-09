#include <stdarg.h>
#include "variadic_functions.h"

/**
 * sum_them_all - Returns the sum of all its parameters.
 * @n: The number of parameters.
 *
 * Return: The sum of parameters.
 */
int sum_them_all(const unsigned int n, ...)
{
    va_list val;
    unsigned int i;
    int sum = 0;

    if (n == 0)
	    return (0);

    va_start(args, n);

    for (i = 0; i < n; i++)
    {
	    sum += va_arg(args, int);
    }

    va_end(val);

    return (sum);
}
