/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: timschmi <timschmi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 18:38:45 by timschmi          #+#    #+#             */
/*   Updated: 2024/09/15 16:22:05 by timschmi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void raycasting(t_game *game)
{
	int x = 0;

	while (x < WIDTH)
	{
		double camx = (2 * x / (double)WIDTH) -1;
		double ray_dir_x = game->player.dir.x + game->player.scr.x * camx;
		double ray_dir_y = game->player.dir.y + game->player.scr.y * camx;

		// int mx = (int)floor(game->player.pos.x / 80);
		// int my = (int)floor(game->player.pos.y / 80);

		int mx = (int)game->player.pos.x;
		int my = (int)game->player.pos.y;

		double sdistx;
		double sdisty;

		double deldistx = fabs(80 / ray_dir_x);
		double deldisty = fabs(80 / ray_dir_y);
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
			sdistx = (mx + 80 - game->player.pos.x) * deldistx;
		}

		if (ray_dir_y < 0)
		{
			stepy = -1;
			sdisty = (game->player.pos.y - my) * deldisty;
		}
		else
		{
			stepy = 1;
			sdisty = (my + 80 - game->player.pos.y) * deldisty;
		}

		int hit = 0;
		int side;
		int ix;
		int iy;
		int i = 0;
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

			int ix = (int)floor(mx / 80);
			int iy = (int)floor(my / 80);

			if (game->map[ix][iy] == 1)
			{
				hit = 1;
				t_point hit;
				hit.x = mx;
				hit.y = my;
				if (i == 0)
				{
					draw_line(&game->player.pos, &hit, game, 0xFF0000FF);
					i = 1;
				}
				else
				 i = 0;
				printf("HIT!!!\n");
			}
			else
				printf("MISS\n");

		}
		x++;
	}
	printf("EXIT\n");
}
