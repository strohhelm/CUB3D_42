#ifndef CUB_H
#define CUB_H

#define WIDTH 800
#define HEIGHT 800

#include <math.h>
#include <stdio.h>
#include "include/libft/libft.h"
#include "include/MLX42/include/MLX42/MLX42.h"

typedef struct s_coordinate {
	double	x;
	double	y;
}	t_point;

typedef struct s_player
{
	int height;
	int width;
	t_point pos;
	t_point dir;
	t_point scr;
	int start;
	long colour;
}	t_player;

typedef struct s_game
{
	mlx_t *mlx;
	mlx_image_t *img;
	t_player player;
	int **map;
} t_game;

//structure of values needed for putting pixels betwwen two points.
typedef struct s_algorythm {
	int		a;
	int		b;
	int		p;
	int		xdiff;
	int		ydiff;
	int		zdiff;
	int		zstep;
	long	col;
	t_point	p_a;
	t_point	p_b;
	t_point	p_t;
}	t_pixel_line;

#endif