/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pstrohal <pstrohal@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 20:09:08 by pstrohal          #+#    #+#             */
/*   Updated: 2024/10/06 16:58:14 by pstrohal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub_bonus.h"

unsigned int	invert_colour(uint8_t *col)
{
	uint8_t	red;
	uint8_t	green;
	uint8_t	blue;
	uint8_t	var;

	var = 80;
	red = (*col) & 0xFF;
	green = (*(col + 1)) & 0xFF;
	blue = (*(col + 2)) & 0xFF;
	red = 255 - red + var;
	green = green + var;
	blue = 255 - blue;
	return(red << 24 | green << 16 | blue << 8 | 255);
}
uint32_t colour(uint8_t *col)
{
	uint8_t r;
	uint8_t g;
	uint8_t b;
	uint8_t a;

	r = *col;
	g = *(col + 1);
	b = *(col + 2);
	a = *(col + 3);
	return (r << 24 | g << 16 | b << 8 | a);
}

void	change_colour(uint32_t col, unsigned int *wall, unsigned int *floor)
{
	uint8_t	red;
	uint8_t	green;
	uint8_t	blue;

	red = ((col) >> 24) & 0xFF;
	green = (col >> 16) & 0xFF;
	blue = (col >> 8) & 0xFF;
	red = 255 - red;
	green = 255 - green;
	blue = 255 - blue;

	*floor = (red << 24 | green << 16 | blue << 8 | 255);
	*wall = (red - 10 )/4 << 24 | (green-10)/4 << 16 | (blue-10)/4 << 8 | 255;
}

void	minimap(t_game * game)
{
	int				w;
	int				h;
	int				printw;
	int				printh;
	double			x = 0.0;
	double			y = 0.0;
	double			step;
	unsigned int	wall = 0;
	unsigned int	floor = 0;
	double			min;
	double			max;
	t_point			pos;
	
	h = 0;
	printh = HEIGHT / 3;
	printw = WIDTH / 4;
	step =  10.0 / printh;
	min = printh/2.0 - 5.0;
	max = printh/2.0 + 5.0;
	change_colour(game->map.ceiling, &wall, &floor);
	while (h <= printh)
	{
		y = h * step; 
		w = 0;
		while (w <= printw)
		{
				x = w * step;
				pos.y = game->player.pos.y - 5 + y;
				pos.x = game->player.pos.x - 5 + x;
			if ((int)pos.x < game->map.map_w && (int)pos.y < game->map.map_h
				&& (int)pos.x >= 0 && (int)pos.y >= 0)
			{
				if (w > min && w < max && h > min && h < max)
					mlx_put_pixel(game->img, w + 10, h + 10, game->map.ceiling);
				else if (game->map.map[(int)pos.y][(int)pos.x] == 1)
					mlx_put_pixel(game->img, w + 10, h + 10, wall);
				else if (game->map.map[(int)pos.y][(int)pos.x] == 0)
					mlx_put_pixel(game->img, w + 10, h + 10, floor);
					// &game->img->pixels[(((h+10) * WIDTH) + w + 10) * 4]
			}
			w++;
		}
		h++;
	}
	t_point	a, b;
	a.x = printh / 2.0 + 10;
	a.y = printh / 2.0 + 10;
	b.x = a.x + game->player.dir.x * 200.0;
	b.y = a.x + game->player.dir.y * 200.0;
	draw_line(&a, &b, game->img, 0xDFFF00FF);
}
	


void circlePoints(int cx, int cy, int x, int y, mlx_image_t *img, uint32_t col)
{
	if (x == 0)
	{
		mlx_put_pixel(img, cx, cy + y, col);
		mlx_put_pixel(img, cx, cy - y, col);
		mlx_put_pixel(img, cx + y, cy, col);
		mlx_put_pixel(img, cx - y, cy, col);
	}
	else if (x == y)
	{
		mlx_put_pixel(img, cx + x, cy + y, col);
		mlx_put_pixel(img, cx - x, cy + y, col);
		mlx_put_pixel(img, cx + x, cy - y, col);
		mlx_put_pixel(img, cx - x, cy - y, col);
	}
	else if (x < y)
	{
		mlx_put_pixel(img, cx + x, cy + y, col);
		mlx_put_pixel(img, cx - x, cy + y, col);
		mlx_put_pixel(img, cx + x, cy - y, col);
		mlx_put_pixel(img, cx - x, cy - y, col);
		mlx_put_pixel(img, cx + y, cy + x, col);
		mlx_put_pixel(img, cx - y, cy + x, col);
		mlx_put_pixel(img, cx + y, cy - x, col);
		mlx_put_pixel(img, cx - y, cy - x, col);
	}
}

void	draw_circle(mlx_image_t *img, uint32_t col, uint32_t radius)
{
	int	x;
	int	y;
	int	xcenter;
	int	ycenter;
	int r2;
	int r;
	int p;

	xcenter = img->height / 2;
	ycenter = img->width / 2;
	if (radius <= img->width / 2 - 1)
		r = radius;
	else
		r = img->width / 2 - 1;
	r2 = r * r;
	y = r;
	p = (5 - r * 4) / 4;
	x = 0;
	circlePoints(xcenter, ycenter, x, y, img, col);
	while (x < y)
	{
		x++;
		if (p < 0)
		{
			p += 2 * x + 1;
		}
		else
		{
			y--;
			p += 2*(x-y)+1;
		}
	circlePoints(xcenter, ycenter, x, y, img, col);
	}
}

// {
// 	int	x;
// 	int	y;
// 	int	xcenter;
// 	int	ycenter;
// 	int r2;
// 	int r;

// 	xcenter = MINIMAP_H / 2;
// 	ycenter = MINIMAP_H / 2;
// 	r = MINIMAP_H / 2;
// 	r2 = r * r;
// 	x = 1;
// 	mlx_put_pixel(game->minimap, xcenter, ycenter + r, 0xFFFFFFFF);
// 	mlx_put_pixel(game->minimap, xcenter, ycenter - r, 0xFFFFFFFF);
// 	while (x <= r)
// 	{
// 		y = (int)(sqrt(r2 - x * x) + 0.5);
// 		mlx_put_pixel(game->minimap, xcenter + x, ycenter + y, 0xFFFFFFFF);
// 		mlx_put_pixel(game->minimap, xcenter + x, ycenter - y, 0xFFFFFFFF);
// 		mlx_put_pixel(game->minimap, xcenter - x, ycenter + y, 0xFFFFFFFF);
// 		mlx_put_pixel(game->minimap, xcenter - x, ycenter - y, 0xFFFFFFFF);
// 		x++;
// 	}	
// }
	
void	minumap(t_game * game)
{
	int				w;
	int				h;
	int				printh;
	double			x = 0.0;
	double			y = 0.0;
	double			step;
	unsigned int	wall = 0;
	unsigned int	floor = 0;
	double			min;
	double			max;
	t_point			pos;
	
	if (mlx_is_key_down(game->mlx, MLX_KEY_UP))
		game->scale += 0.1;
	else if (mlx_is_key_down(game->mlx, MLX_KEY_DOWN))
		game->scale -= 0.1;
	h = 0;
	printh = MINIMAP_H;
	step = game->scale / (double)printh;
	min = MINIMAP_H/2.0 - 5.0;
	max = MINIMAP_H/2.0 + 5.0;
	change_colour(game->map.ceiling, &wall, &floor);
	while (h < printh)
	{
		y = h * step;
		w = 0;
		while (w < printh)
		{
				x = w * step;
				pos.y = game->player.pos.y - game->scale/2 + y;
				pos.x = game->player.pos.x - game->scale/2 + x;
			if (!colour(&game->circle->pixels[(((h) * game->circle->width) + w) * 4]))
			{
				mlx_put_pixel(game->minimap, w, h, 0x00000000);
				// mlx_put_pixel(game->minimap, w, h, colour(&game->img->pixels[(((h + MINIMAP_P) * game->img->width) + w + MINIMAP_P) * 4]));
				// if (colour(&game->img->pixels[(((h + MINIMAP_P) * game->img->width) + w + MINIMAP_P) * 4]) == SO)
				// 	mlx_put_pixel(game->minimap, w, h, SO);
				 if ((int)pos.x < game->map.map_w && (int)pos.y < game->map.map_h
					&& (int)pos.x >= 0 && (int)pos.y >= 0)
				{
					if (w > min && w < max && h > min && h < max)
						mlx_put_pixel(game->minimap, w, h, game->map.ceiling);
					else if (game->map.map[(int)pos.y][(int)pos.x] == 1)
						mlx_put_pixel(game->minimap, w, h, wall);
					else if (game->map.map[(int)pos.y][(int)pos.x] == 0)
						mlx_put_pixel(game->minimap, w, h, floor);
				}
			}
			w++;
		}
		h++;
	}
}
void	fill_outside_circle(mlx_image_t *img)
{
	u_int32_t		x;
	u_int32_t		y;
	bool	inside;
	bool	line;

	y = -1;
	inside = false;
	line = false;
	while (++y < img->height)
	{
		x = -1;
		while (++x < img->width / 2 && colour(&img->pixels[((y * img->width) + x) * 4]) != 0xFFFFFFFF)
				mlx_put_pixel(img, x, y, 0xFFFFFFFF);
		x = img->width;
		while (--x > img->width / 2 && colour(&img->pixels[((y * img->width) + x) * 4]) != 0xFFFFFFFF)
				mlx_put_pixel(img, x, y, 0xFFFFFFFF);
	}
}

void	minimap_init(t_game *game)
{
	game->circle = mlx_new_image(game->mlx, (uint32_t)MINIMAP_W, (uint32_t)MINIMAP_H);
	if (!game->circle)
		error_print("Oh shit circle img failed!");
	draw_circle(game->circle, 0xFFFFFFFF, game->circle->width / 2 - 1);
	fill_outside_circle(game->circle);
}

// *((uint32_t*)&game->img->pixels[(((h) * WIDTH) + w) * 4])