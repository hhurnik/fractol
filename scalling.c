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

double	ft_scale(double nb, double new_min, double new_max,
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