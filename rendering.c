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

// rendering Mandelbrod fractal
void	fractal_render(t_fractal *fractal)
{
	int	x;
	int	y;

	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			ft_handle_pixel(x, y, fractal);
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(fractal->mlx_connection, fractal->mlx_window,
		fractal->img.img_ptr, 0, 0);
}

// Function checks if imaginary point z = x + yi belongs to Mandelbrod set
void	ft_handle_pixel(int x, int y, t_fractal *fractal)
{
	t_complex	z;
	t_complex	c;
	int		i;
	int		color;

	z.real = rescale(x, -2, +2, WIDTH) * fractal->zoom + fractal->shift_x;
	z.imaginary = rescale(y, +2, -2, HEIGHT) * fractal->zoom + fractal->shift_y;
	ft_mandelbrot_julia(&z, &c, fractal);
	i = 0;
	while (i < fractal->check_i)
	{
		z = sum_complex(square_complex(z), c);
		if ((z.real * z.real) + (z.imaginary * z.imaginary) > fractal->escape_value)
		{
			color = rescale(i, BLACK, WHITE, fractal->check_i);
			ft_pixel_put(x, y, &fractal->img, color);
			return ;
		}
		i++;
	}
	ft_pixel_put(x, y, &fractal->img, AURORA_GREEN);
}

//defines the pixel in the pixel buffer
void	ft_pixel_put(int x, int y, t_img *img, int color)
{
	int	offset;

	offset = (y * img->line_len) + (x * (img->bpp / 8));
	*(unsigned int *)(img->pix_ptr + offset) = color;
}


//Function toggling between mandelbrot and julia fractal sets
void	ft_mandelbrot_julia(t_complex *z, t_complex *c, t_fractal *fractal)
{
	if (ft_strncmp(fractal->name, "julia", 5) == 0)
	{
		c->real = fractal->julia_real;
		c->imaginary = fractal->julia_imaginary;
	}
	else
	{
		c->real = z->real;
		c->imaginary = z->imaginary;
	}
}