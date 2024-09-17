/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: timschmi <timschmi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 18:38:45 by timschmi          #+#    #+#             */
/*   Updated: 2024/09/17 14:23:54 by timschmi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void raycasting(t_game *game)
{
	int x = 0;

	while (x < 800)
	{
		double camx = 2 * x / (double)800 -1;
		double ray_dir_x = game->player.dir.x + game->player.scr.x * camx;
		double ray_dir_y = game->player.dir.y + game->player.scr.y * camx;

		int mx = (int)(game->player.pos.x);
		int my = (int)(game->player.pos.y);

		// printf("map(x: %d, y: %d)\n", mx, my);

		double sdistx;
		double sdisty;

		double deldistx = fabs(1 / ray_dir_x);
		double deldisty = fabs(1 / ray_dir_y);
		double walldist;

		int stepx;
		int stepy;

		if (ray_dir_x < 0)
		{
			stepx = -1;
			sdistx = (game->player.pos.x - mx) * deldistx;
		}
		else
		{
			stepx = 1;
			sdistx = (mx + 1.0 - game->player.pos.x) * deldistx;
		}

		if (ray_dir_y < 0)
		{
			stepy = -1;
			sdisty = (game->player.pos.y - my) * deldisty;
		}
		else
		{
			stepy = 1;
			sdisty = (my + 1.0 - game->player.pos.y) * deldisty;
		}

		int hit = 0;
		int side;

		while(hit == 0)
		{
			if (sdistx < sdisty)
			{
				sdistx += deldistx;
				mx += stepx;
				side = 0;
			}
			else
			{
				sdisty += deldisty;
				my += stepy;
				side = 1;
			}
			// printf("map(x: %d, y: %d)\n", mx, my);
			if (game->map.map[mx][my] == 1)
			{
				hit = 1;

			}
		}
		if (side == 0)
		{
			walldist = sdistx - deldistx;
		}
		else
		{
			walldist = sdisty - deldisty;
		}
		t_point hitp;
		hitp.x = game->player.pos.x + walldist *ray_dir_x;
		hitp.y = game->player.pos.y + walldist *ray_dir_y;
		draw_line(&game->player.pos, &hitp, game, 0xFF0000FF);

		int lineheight = HEIGHT / walldist;
		int start = -lineheight / 2 + HEIGHT / 2;
		if (start < 0)
			start = 0;
		int end = lineheight / 2 + HEIGHT / 2;
		if (end >= HEIGHT)
			end = HEIGHT - 1;
		while(start <= end)
		{
			int color;
			if (side == 0)
				color = 0xFF0000FF;
			else
				color = 0xFFFF00FF;
			mlx_put_pixel(game->img, x + 800, start, color);
			start++;
		}
		x++;
	}
}
