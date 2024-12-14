#include "fractol.h"


int	key_handler(int keysym, t_fractal *fractal)
{
	if (keysym == XK_Escape)
		close_handler(fractal);
	else if (keysym == XK_Left)
		fractal->shift_x -= 0.5 * fractal->zoom;
	else if (keysym == XK_Right)
		fractal->shift_x += 0.5 * fractal->zoom;
	else if (keysym == XK_Up)
		fractal->shift_y += 0.5 * fractal->zoom;
	else if (keysym == XK_Down)
		fractal->shift_y -= 0.5 * fractal->zoom;
	else if (keysym == XK_period)
		fractal->check_i += 10;
	else if (keysym == XK_comma)
		fractal->check_i -= 10;
	fractal_render(fractal);
	return (0);
}
int	mouse_handler(int button, int x, int y, t_fractal *fractal)
{
	(void) x;
	(void) y;
	if (button == 4)
		fractal->zoom *= 0.95;
	if (button == 5)
		fractal->zoom *= 1.05;
	fractal_render(fractal);
	return (0);
}

int	close_handler(t_fractal *fractal)
{
	mlx_destroy_image(fractal->mlx_connection, fractal->img.img_ptr);
	mlx_destroy_window(fractal->mlx_connection, fractal->mlx_window);
	mlx_destroy_display(fractal->mlx_connection);
	free(fractal->mlx_connection);
	exit(EXIT_SUCCESS);
}

#include "fractol.h"

double double_atoi(char *s)
{
    long integer_part;     // To store the integer part of the number
    double fractional_part; // To store the fractional part of the number
    int sign;   
	integer_part = 0;
	fractional_part = 0;
	sign = 1;

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

int	main(int argc, char *argv[])
{
	t_fractal	fractal;

	if ((argc == 2 && !ft_strncmp(argv[1], "mandelbrot", 10))
		|| (argc == 4 && !ft_strncmp(argv[1], "julia", 5)))
	{
		fractal.name = argv[1];
		if (!ft_strncmp(argv[1], "julia", 5))
			ft_collect_julia_values(argv[2], argv[3], &fractal);
		fractal_init(&fractal);
		fractal_render(&fractal);
		mlx_loop(fractal.mlx_connection);
	}
	else
	{
		printf("Please enter\n./fractol mandelbrot\n");
		printf("or\n./fractol julia <real> <i>\n");
		exit(EXIT_FAILURE);
	}
	return (0);
}

static void	ft_collect_julia_values(char *r, char *i, t_fractal *fractal)
{
	double	tmp;

	tmp = double_atoi(r);
	if (!tmp)
		exit(EXIT_FAILURE);
	else
	{
		fractal->julia_real = tmp;
		tmp = double_atoi(i);
		if (!tmp)
			exit(EXIT_FAILURE);
		else
			fractal->julia_imaginarymaginarymaginarymaginarymaginary = tmp;
	}
}


void	fractal_init(t_fractal *fractal)
{
	fractal->mlx_connection = mlx_init();
	if (fractal->mlx_connection == NULL)
		ft_malloc_error();
	fractal->mlx_window = mlx_new_window(fractal->mlx_connection,
			WIDTH, HEIGHT, fractal->name);
	if (fractal->mlx_window == NULL)
	{
		mlx_destroy_display(fractal->mlx_connection);
		free(fractal->mlx_connection);
		ft_malloc_error();
	}
	fractal->img.img_ptr = mlx_new_image(fractal->mlx_connection,
			WIDTH, HEIGHT);
	if (fractal->img.img_ptr == NULL)
	{
		mlx_destroy_window(fractal->mlx_connection, fractal->mlx_window);
		mlx_destroy_display(fractal->mlx_connection);
		free(fractal->mlx_connection);
		ft_malloc_error();
	}
	fractal->img.pix_ptr = mlx_get_data_addr(fractal->img.img_ptr,
			&fractal->img.bpp, &fractal->img.line_len, &fractal->img.endian);
	events_init(fractal);
	data_init(fractal);
}

static void	data_init(t_fractal *fractal)
{
	fractal->escape_value = 4;
	fractal->check_i = 42;
	fractal->shift_x = 0;
	fractal->shift_y = 0;
	fractal->zoom = 1.0;
}

static void	events_init(t_fractal *fractal)
{
	mlx_hook(fractal->mlx_window,
		KeyPress, KeyPressMask, key_handler, fractal);
	mlx_hook(fractal->mlx_window,
		ButtonPress, ButtonPressMask, mouse_handler, fractal);
	mlx_hook(fractal->mlx_window,
		DestroyNotify, StructureNotifyMask, close_handler, fractal);
}

/**
 * Function handling failure to allocate mlx structures
 *
 */
static void	ft_malloc_error(void)
{
	printf("\nProblems with mlx variables initialization!\n");
	exit(EXIT_FAILURE);
}

t_complex	sum_complex(t_complex x, t_complex y)
{
	t_complex	result;

	result.r = x.r + y.r;
	result.i = x.i + y.i;
	return (result);
}

// the result of squaring a complex number
// has a real and imaginary part
// x^2 - y^2 + 2xyi
// i return the result in two parts
t_complex	square_complex(t_complex z)
{
	t_complex	result;

	result.r = (z.r * z.r) - (z.i * z.i);
	result.i = 2 * z.r * z.i;
	return (result);
}

void	fractal_render(t_fractal *fractal)
{
	int	x;
	int	y;

	y = -1;
	while (++y < HEIGHT)
	{
		x = -1;
		while (++x < WIDTH)
			ft_handle_pixel(x, y, fractal);
	}
	mlx_put_image_to_window(fractal->mlx_connection, fractal->mlx_window,
		fractal->img.img_ptr, 0, 0);
}

/**
 * Function checks if imaginary point z = x + yi belongs to Mandelbrod set
 *
 * Theorem used:
 * - ???
 * - complex numbers calculus
 * - Pythagoram theorem
 */
static void	ft_handle_pixel(int x, int y, t_fractal *fractal)
{
	t_complex	z;
	t_complex	c;
	int		i;
	int		color;

	z.r = ft_scale(x, -2, +2, WIDTH) * fractal->zoom + fractal->shift_x;
	z.i = ft_scale(y, +2, -2, HEIGHT) * fractal->zoom + fractal->shift_y;
	ft_mandelbrot_julia(&z, &c, fractal);
	i = 0;
	while (i < fractal->check_i)
	{
		z = sum_complex(square_complex(z), c);
		if ((z.r * z.r) + (z.i * z.i) > fractal->escape_value)
		{
			color = ft_scale(i, BLACK, WHITE, fractal->check_i);
			ft_pixel_put(x, y, &fractal->img, color);
			return ;
		}
		i++;
	}
	ft_pixel_put(x, y, &fractal->img, AURORA_GREEN);
}

/**
 * Function defines the pixel in the pixel buffer
 *
 */
static void	ft_pixel_put(int x, int y, t_img *img, int color)
{
	int	offset;

	offset = (y * img->line_len) + (x * (img->bpp / 8));
	*(unsigned int *)(img->pix_ptr + offset) = color;
}

/**
 * Function toggling between mandelbrot and julia fractal sets
 *
 */
static void	ft_mandelbrot_julia(t_complex *z, t_complex *c, t_fractal *fractal)
{
	if (!ft_strncmp(fractal->name, "julia", 5))
	{
		c->r = fractal->julia_real;
		c->i = fractal->julia_imaginary;
	}
	else
	{
		c->r = z->r;
		c->i = z->i;
	}
}

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

// adn this is header:
#ifndef FRACTOL_H
# define FRACTOL_H

# include "minilibx_linux/mlx.h"
# include <X11/X.h>
# include <X11/keysym.h>
# include <math.h>
# include <stdlib.h> // malloc free exit
#include <stdio.h> //printf - usunac

# define WIDTH 800
# define HEIGHT 800

// Basic colors
# define BLACK 0x000000 // Black
# define WHITE 0xFFFFFF // White

// Psychedelic colors
// # define NEON_GREEN 0x39FF14    // Bright neon green
// # define HOT_PINK 0xFF1493      // Hot pink
// # define ELECTRIC_BLUE 0x2C75FF // Vibrant electric blue
// # define LIME_YELLOW 0xCCFF00   // Lime yellow
// # define FIERY_RED 0xFF2400     // Fiery red
// # define ORANGE_PEEL 0xFFA500   // Psychedelic orange
// # define ULTRA_VIOLET 0x800080  // Deep ultraviolet purple
// # define CYAN_SPARKLE 0x00FFFF  // Cyan sparkle
// # define MAGENTA_RUSH 0xFF00FF  // Vivid magenta

# define CHARTREUSE_GLARE 0x7FFF00   // Bold chartreuse green
# define PLASMA_YELLOW 0xFFD700   // Intense golden yellow
# define ELECTRO_INDIGO 0x4B0082   // Electric indigo blue
# define LUCID_TEAL 0x008080   // Hypnotic teal
# define SUNBURST_GOLD 0xFFC300   // Vibrant sunburst gold
# define HYPER_ORANGE 0xFF7F50   // Bright coral orange
# define PSY_TRIBAL_PURPLE 0x9400D3 // Deep glowing purple
# define AURORA_GREEN 0x00FA9A  // Neon aurora green
# define BLAZE_RED 0xFF0033    // Explosive vivid red

// Structure used as a pixel buffer
typedef struct s_img
{
	void	*img_ptr; // pointer to image struct
	char	*pix_ptr;
	int		bpp; // bits per pixel
	int		endian;
	int		line_len;
}	t_img;

/**
 * Structure containing all the necessary data to draw a fractal
 * in my application
 * ~ MLX wiring
 * ~ Image structure
 * ~ Hooks values
 */
typedef struct s_fractal
{
	char	*name;
	void	*mlx_connection;
	void	*mlx_window;
	t_img	img;
	double	escape_value;
	int		check_i;
	double	shift_x;
	double	shift_y;
	double	zoom;
	double	julia_real;
	double	julia_imaginarymaginarymaginary;
}	t_fractal;

/**
 * Structure containing complex numbers with:
 * r - standing for real component
 * i - standing for imaginary component
 *
 */
typedef struct s_cmplx
{
	double	r;
	double	i;
}	t_complex;

/**
 * Program functions
 *
 */
double	ft_fractol_atodbl(char *s);
void	fractal_init(t_fractal *fractal);
void	fractal_render(t_fractal *fractal);
double	ft_scale(double nb, double new_min, double new_max,
			double old_max);
t_complex	sum_complex(t_complex x, t_complex y);
t_complex	square_complex(t_complex c);
int	mouse_handler(int button, int x, int y, t_fractal *fractal);
int		close_handler(t_fractal *fractal);
// int		julia_track(int x, int y, t_fractal *fractal);
int		key_handler(int keysym, t_fractal *fractal);


int	ft_strncmp(char *s1, char *s2, int n);
long parse_integer(char **s_ptr);
double parse_fractional(char *s);
double double_atoi(char *s);


#endif

