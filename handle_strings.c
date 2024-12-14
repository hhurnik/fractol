/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 17:48:23 by marvin            #+#    #+#             */
/*   Updated: 2024/12/12 17:48:23 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	ft_strncmp(char *s1, char *s2, int n)
{
	if (NULL == s1 || NULL == s2 || n <= 0)
		return (0);
	while (*s1 == *s2 && n > 0 && *s1 != '\0')
	{
		++s1;
		++s2;
		--n;
	}

	return (*s1 - *s2);
}

void	ft_putstr_fd(char *s, int fd)
{
    int	i;

	i = 0;
	while (s[i] != '\0')
		i++;
	
	write(fd, s, i);
}

double double_atoi(char *s)
{
    long integer_part;     // To store the integer part of the number
    double fractional_part; // To store the fractional part of the number
    int sign;   
	integer_part = 0;
	fractional_part = 0;
	sign = 1;

    not_digits(s);
    while ((*s >= 9 && *s <= 13) || *s == 32)
        s++;

    while (*s == '+' || *s == '-')
    {
        if (*s == '-')
            sign = -sign;
        s++;
    }

    integer_part = parse_integer(&s);

    if (*s == '.')
    {
        s++;
        fractional_part = parse_fractional(s);
    }
    return (integer_part + fractional_part) * sign;
}

void not_digits(char *s)
{
    while(*s)
    {
        if (!(*s >= '0' && *s <= '9'))
        {
            ft_putstr_fd("Enter ./fractol mandelbrot or ./fractol julia <real_part>  <imaginary_part>\n", 2);
            exit(EXIT_FAILURE);
        }
        s++;
    }
}

long parse_integer(char **s_ptr)
{
    long integer_part = 0;
    char *s = *s_ptr;

    // Parse the integer part of the number
    while (*s >= '0' && *s <= '9')
    {
        integer_part = (integer_part * 10) + (*s - '0');
        s++;
    }

    *s_ptr = s; // Update the pointer to reflect the consumed characters
    return integer_part;
}

double parse_fractional(char *s)
{
    double fractional_part = 0;
    double pow = 1;

    // Parse the fractional part of the number
    while (*s >= '0' && *s <= '9')
    {
        pow /= 10; // Move one decimal place
        fractional_part += (*s - '0') * pow;
        s++;
    }

    return fractional_part;
}

