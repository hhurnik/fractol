#ifndef FRACTOL_H
# define FRACTOL_H

# include "minilibx_linux/mlx.h"
# include <X11/X.h>
# include <X11/keysym.h>
# include <math.h>
# include <stdlib.h> // malloc free exit
#include <unistd.h> //write

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


//bpp is 32, then each pixel is represented by 4 bytes 
//(8 bits per channel: Red, Green, Blue, and Alpha
// Structure used as a pixel buffer
typedef struct s_img
{
	void	*img_ptr; // pointer to image struct
	char	*pix_ptr;
	int		bpp; // bits per pixel
	int		endian;
	int		line_len;
}	t_img;

// Structure containing all the necessary data to draw a fractal
// -MLX wiring
// -Image structure
// -Hooks values
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
	double	julia_imaginary;
}	t_fractal;

// Structure containing complex numbers
typedef struct s_complex
{
	double	real;
	double	imaginary;
}	t_complex;



// events
int	key_handler(int keysym, t_fractal *fractal);
int	mouse_handler(int button, int x, int y, t_fractal *fractal);
int	close_handler(t_fractal *fractal);

// handle_strings
void	ft_putstr_fd(char *s, int fd);
int	ft_strncmp(char *s1, char *s2, int n);
long parse_integer(char **s_ptr);
double parse_fractional(char *s);
double double_atoi(char *s);
void not_digits(char *s);

// init
void	data_init(t_fractal *fractal);
void	fractal_init(t_fractal *fractal);
void	events_init(t_fractal *fractal);
void	ft_malloc_error(void); //czy moge wyrzucic?

//math
t_complex	sum_complex(t_complex x, t_complex y);
t_complex	square_complex(t_complex z);
double	rescale(double nb, double new_min, double new_max, double old_max);

//rendering
void	fractal_render(t_fractal *fractal);
void	ft_handle_pixel(int x, int y, t_fractal *fractal);
void	ft_pixel_put(int x, int y, t_img *img, int color);
void	ft_mandelbrot_julia(t_complex *z, t_complex *c, t_fractal *fractal);



#endif