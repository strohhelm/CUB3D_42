/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pstrohal <pstrohal@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 18:38:45 by timschmi          #+#    #+#             */
/*   Updated: 2024/09/18 16:53:26 by pstrohal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

int	get_colour(t_point pos, t_point hit, int side)
{
	if (pos.x <= hit.x && pos.y >= hit.y)
	{
		if (side == 0)
			return (EA);
		else
			return (NO);
	}
	else if (pos.x >= hit.x && pos.y >= hit.y)
	{
		if (side == 0)
			return (WE);
		else
			return (NO);
	}
	else if (pos.x >= hit.x && pos.y <= hit.y)
	{
		if (side == 0)
			return (WE);
		else
			return (SO);
	}
	else if ((pos.x <= hit.x && pos.y <= hit.y))
	{
		if (side == 0)
			return (EA);
		else
			return (SO);
	}
	else
		return (0);
}

void	draw_tex(t_game *game, int x, int start, int end, t_point hit)
{
	double step;
	int i;
	int colour;
	double x_scale;
	int arr_pos;

	i = 0;
	step = game->map.north->height / (end - start);
	hit.x /= game->map.scale;
	hit.y /= game->map.scale;
	hit.x = fmod(hit.x, 1.0);
	x_scale = game->map.north->width * hit.x;
	
	while (i <= (end - start))
	{
		arr_pos = (i * (int)step) * game->map.north->width + (int)x_scale;
		colour = game->map.north->pixels[arr_pos];
		
		colour = colour | 0xFF;
		printf("py: %d, px : %d\n", i * (int)step, (int)x_scale);
		printf("value:%x arr pos:%d\n", colour, arr_pos);
		mlx_put_pixel(game->img, x + (WIDTH / 2), start + i, colour);
		i++;
	}
	
}

void	raycasting(t_game *game)
{
	int x = 0;

	while (x < WIDTH/2)
	{
		double camx = 2 * x / (double)(WIDTH / 2) -1;
		// double camx = 0;

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
			if (game->map.map[my][mx] == 1)
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
		t_point pos;
		hitp.x = (game->player.pos.x + walldist *ray_dir_x) * game->map.scale;
		hitp.y = (game->player.pos.y + walldist *ray_dir_y) * game->map.scale;
		pos.x = game->player.pos.x *game->map.scale;
		pos.y = game->player.pos.y *game->map.scale;
		if (x %15 == 0)
		draw_line(&pos, &hitp, game, 0xFF0000FF);

		int lineheight = HEIGHT / walldist;
		int start = -lineheight / 2 + HEIGHT / 2;
		if (start < 0)
			start = 0;
		int end = lineheight / 2 + HEIGHT / 2;
		if (end >= HEIGHT)
			end = HEIGHT - 1;
			// printf("posx: %f y: %f | hitx: %f y: %f side :%d\n", pos.x, pos.y, hitp.x, hitp.y, side);
			int colour = get_colour(pos, hitp, side);
		if (colour == NO)
			draw_tex(game, x, start, end, hitp);
		else
		{
			while(start <= end)
			{
				mlx_put_pixel(game->img, x + (WIDTH / 2), start, colour);
				start++;
			}
		}
		x++;
	}
}
