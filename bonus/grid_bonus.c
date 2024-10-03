/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grid_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pstrohal <pstrohal@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 16:18:23 by timschmi          #+#    #+#             */
/*   Updated: 2024/10/03 19:54:57 by pstrohal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub_bonus.h"

void	color_cell(t_game *game, int fy, int fx, int x, int y)
{
	if (game->map.map[fy][fx] == 1)
		mlx_put_pixel(game->img, x, y, 0xD3D3D3FF);
	else if (game->map.map[fy][fx] == 0)
		mlx_put_pixel(game->img, x, y, 0x808080FF);
	else if (game->map.map[fy][fx] == -1)
		mlx_put_pixel(game->img, x, y, 0x000000FF);
}

void	grid(t_game *game)
{
	int	x;
	int	y;
	int	fy;
	int	fx;

	x = 0;
	y = 0;
	while (y < HEIGHT)
	{
		fy = (int)y / game->map.scale;
		x = 0;
		while (x < WIDTH / 2)
		{
			fx = (int)x / game->map.scale;
			if (fx < game->map.map_w && fy < game->map.map_h)
				color_cell(game, fy, fx, x, y);
			x++;
		}
		y++;
	}
}
