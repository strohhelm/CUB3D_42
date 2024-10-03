/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pstrohal <pstrohal@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 20:09:08 by pstrohal          #+#    #+#             */
/*   Updated: 2024/10/03 23:23:36 by pstrohal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub_bonus.h"

void	change_colour(unsigned int col, unsigned int *wall, unsigned int *floor)
{
	uint8_t	red;
	uint8_t	green;
	uint8_t	blue;

	red = (col >> 24) & 0xFF;
	green = (col >> 16) & 0xFF;
	blue = (col >> 8) & 0xFF;
	red = 255 - red;
	green = 255 - green;
	blue = 255 - blue;
	*floor = (red - 10 )/2 << 24 | (green-10)/2 << 16 | (blue-10)/2 << 8 | 255;
	*wall = red << 24 | green << 16 | blue << 8 | 255;
}

void	minimap(t_game * game)
{
	int				w;
	int				h;
	// int				printw;
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
	step =  10.0 / printh;
	min = printh/2.0 - 5.0;
	max = printh/2.0 + 5.0;
	change_colour(game->map.ceiling, &wall, &floor);
	while (h <= printh)
	{
		y = h * step; 
		w = 0;
		while (w <= printh)
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
	draw_line(&a, &b, game, 0xDFFF00FF);
}
