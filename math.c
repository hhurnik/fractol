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


//Function implementing the formula for squarying a complex number:
// real = (real_number^2 - imaginary_number^2)
// img = 2 * r * i
// using the same notation as in my t_complex structure)

t_complex	square_complex(t_complex z)
{
	t_complex	result;

	result.real = (z.real * z.real) - (z.imaginary * z.imaginary);
	result.imaginary = 2 * z.real * z.imaginary;
	return (result);
}