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


// vector add x and y complex numbers
t_complex	sum_complex(t_complex x, t_complex y)
{
	t_complex	result;

	result.real = x.real + y.real;
	result.imaginary = x.imaginary + y.imaginary;
	return (result);
}


// the result of squaring a complex number
// has a real and imaginary part
// x^2 - y^2 + 2xyi
// i return the result in two parts
t_complex	square_complex(t_complex z)
{
	t_complex	result;

	result.real = (z.real * z.real) - (z.imaginary * z.imaginary);
	result.imaginary = 2 * z.real * z.imaginary;
	return (result);
}

double	rescale(double nb, double new_min, double new_max,
	double old_max)
{
	double	a;
	double	b;
	double	old_min;

	old_min = 0.0;
	a = new_max - new_min;
	b = old_max - old_min;
	return ((a) * (nb - old_min) / (b) + new_min);
}