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

int	main(int argc, char *argv[])
{
	t_fractal	fractal;


	if ((argc == 2 && ft_strncmp(argv[1], "mandelbrot", 10) == 0) || 
		(argc == 4 && ft_strncmp(argv[1], "julia", 5) == 0))
	{
		fractal.name = argv[1];
		if (ft_strncmp(fractal.name, "julia", 5) == 0)
		{
			fractal.julia_real = double_atoi(argv[2]);
			fractal.julia_imaginary = double_atoi(argv[3]);
		}

		fractal_init(&fractal);
		
		fractal_render(&fractal);
		
		//a loop listening for events like clicking the mouse and others
		//it says to keep listening
		mlx_loop(fractal.mlx_connection);
	}
	else
	{
		ft_putstr_fd("Enter ./fractol mandelbrot or ./fractol julia <real_part> <imaginary_part>\n", 2);
		exit(EXIT_FAILURE);
	}
}
