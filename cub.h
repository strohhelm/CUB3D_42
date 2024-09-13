#ifndef CUB_H
#define CUB_H

#define WIDTH 800
#define HEIGHT 800

#include <math.h>
#include <stdio.h>
#include "include/libft/libft.h"
#include "include/MLX42/include/MLX42/MLX42.h"

typedef struct player_s
{
	double x_pos;
	double y_pos;
	int start;
	mlx_t *mlx;
	mlx_image_t *img;
}	player_t;


#endif