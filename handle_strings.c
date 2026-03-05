/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_strings.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhurnik <hhurnik@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 15:59:48 by hhurnik           #+#    #+#             */
/*   Updated: 2024/12/14 15:59:48 by hhurnik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	ft_strncmp(char *s1, char *s2, int n)
{
	if (s1 == NULL || s2 == NULL || n <= 0)
		return (0);
	while (*s1 == *s2 && n > 0 && *s1 != '\0')
	{
		s1++;
		s2++;
		n--;
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

long	parse_integer(char **s_ptr)
{
	long	integer_part;
	char	*s;

	integer_part = 0;
	s = *s_ptr;
	while (*s >= '0' && *s <= '9')
	{
		integer_part = (integer_part * 10) + (*s - '0');
		s++;
	}
	*s_ptr = s;
	return (integer_part);
}

double	parse_fractional(char **s_ptr)
{
	double	fractional_part;
	double	pow;
	char	*s;

	fractional_part = 0;
	pow = 1;
	s = *s_ptr;
	while (*s >= '0' && *s <= '9')
	{
		pow /= 10;
		fractional_part += (*s - '0') * pow;
		s++;
	}
	*s_ptr = s;
	return (fractional_part);
}

double	double_atoi(char *s)
{
	long	integer_part;
	double	fractional_part;
	int		sign;

	integer_part = 0;
	fractional_part = 0;
	sign = 1;
	while ((*s >= 9 && *s <= 13) || *s == 32)
		s++;
	if (*s == '+' || *s == '-')
	{
		if (*s == '-')
			sign = -sign;
		s++;
	}
	integer_part = parse_integer(&s);
	if (*s == '.')
	{
		s++;
		fractional_part = parse_fractional(&s);
	}
	error_message(s);
	return ((integer_part + fractional_part) * sign);
}
