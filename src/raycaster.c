/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pstrohal <pstrohal@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 18:38:45 by timschmi          #+#    #+#             */
/*   Updated: 2024/09/23 21:02:20 by pstrohal         ###   ########.fr       */
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

void	draw_tex(t_game *game, int x, t_point line, int dir, t_point hit)
{
	double step;
	int i;
	double x_scale;
	uint8_t *tex_pos;
	uint8_t *img_pos;
	
	i = 0;
	step = 1.0 * game->map.textures[dir]->height / (line.y - line.x);
	if (dir ==  NO || dir == SO)
		x_scale = (double)game->map.textures[dir]->height * fmod(hit.x, 1.0);
	else if (dir == WE || dir == EA)
		x_scale = (double)game->map.textures[dir]->height * fmod(hit.y, 1.0);
	
	while (i <= (line.y - line.x))
	{
		if (!(line.x + i < 0 || line.x + i > HEIGHT))
		{
			int tex_y =(int)i * step;
			int arr_pos = (tex_y * game->map.textures[dir]->width + (int)x_scale) * game->map.textures[dir]->bytes_per_pixel;
			
			tex_pos = &game->map.textures[dir]->pixels[arr_pos];
			int pic_pos = ((line.x + i) * game->img->width + (x + WIDTH / 2)) * game->map.textures[dir]->bytes_per_pixel;
			
			img_pos = &game->img->pixels[pic_pos];
			ft_memmove(img_pos, tex_pos, game->map.textures[dir]->bytes_per_pixel);
		}
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
			// printf("map(x: %d, y: %d\n w:%d, h:%d\n)\n", mx, my, game->map.map_w, game->map.map_h);
			if ((mx < 0 || mx > game->map.map_w - 1))
			{
				if (mx < 0)
					mx += 1;
				else 
					mx -= 1;
				hit = 1;
			}
			else if (my < 0 || my > game->map.map_h -1 )
			{
				if (my < 0)
					my += 1;
				else 
					my -= 1;
				hit = 1;
			}
			else if (game->map.map[my][mx] == 1)
			{
				hit = 1;
			}
		}
		if (side == 0)
		{
			walldist = (sdistx - deldistx) / 10;
		}
		else
		{
			walldist = (sdisty - deldisty) / 10;
		}
		t_point hitp;
		t_point pos;
		t_point wallhit;
		t_point ray;
		ray.x = ray_dir_x;
		ray.y = ray_dir_y;
		wallhit.x = game->player.pos.x + walldist * 10 *ray_dir_x;
		wallhit.y = game->player.pos.y + walldist * 10 *ray_dir_y;
		
		hitp.x = (game->player.pos.x + walldist * 10 *ray_dir_x) * game->map.scale;
		hitp.y = (game->player.pos.y + walldist *10 * ray_dir_y) * game->map.scale;
		
		pos.x = game->player.pos.x *game->map.scale;
		pos.y = game->player.pos.y *game->map.scale;
		
		if (x %15 == 0)
			draw_line(&pos, &hitp, game, 0xFF0000FF);
		int direction = get_colour(pos, hitp, side);

		int lineheight = HEIGHT / walldist;
		int start = -lineheight / 2 + HEIGHT / 2;
		if (direction != NO && start < 0)
			start = 0;
		int end = lineheight / 2 + HEIGHT / 2;
		if (direction != NO && end >= HEIGHT)
			end = HEIGHT - 1;
		t_point line;
		line.x = start;
		line.y = end;
		draw_tex(game, x, line, direction, wallhit);
		x++;
	}
}
