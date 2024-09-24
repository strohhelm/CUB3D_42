/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: timschmi <timschmi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 18:38:45 by timschmi          #+#    #+#             */
/*   Updated: 2024/09/24 15:57:27 by timschmi         ###   ########.fr       */
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

void	draw_tex(t_game *game, int x, int start, int end, t_point hit, t_point ray, int side)
{
	double step;
	int i;
	double x_scale;
	uint8_t *tex_pos;
	uint8_t *img_pos;
	
	i = 0;
	step = 1.0 * game->map.north->height / (end - start);

	x_scale = (double)game->map.north->height * fmod(hit.x, 1.0);

	while (i <= (end - start))
	{
		if (!(start + i < 0 || start + i > HEIGHT))
		{
			int tex_y =(int)i * step;
			int arr_pos = (tex_y * game->map.north->width + (int)x_scale) * game->map.north->bytes_per_pixel;
			
			tex_pos = &game->map.north->pixels[arr_pos];
			int pic_pos = ((start + i) * game->img->width + (x + WIDTH / 2)) * game->map.north->bytes_per_pixel;
			
			img_pos = &game->img->pixels[pic_pos];
			ft_memmove(img_pos, tex_pos, game->map.north->bytes_per_pixel);
		}
		i++;
	}
	
}

void init_rays(t_game *game, t_rays *rays, int x)
{
	rays->camx = 2 * x / (double)(WIDTH / 2) -1;
	rays->ray_dir_x = game->player.dir.x + game->player.scr.x * rays->camx;
	rays->ray_dir_y = game->player.dir.y + game->player.scr.y * rays->camx;
	rays->mx = (int)(game->player.pos.x);
	rays->my = (int)(game->player.pos.y);
	rays->deldistx = fabs(1 / rays->ray_dir_x);
	rays->deldisty = fabs(1 / rays->ray_dir_y);
	rays->hit = 0;
}


void step_and_dist(t_game *game, t_rays *rays)
{
	if (rays->ray_dir_x < 0)
	{
		rays->stepx = -1;
		rays->sdistx = (game->player.pos.x - rays->mx) * rays->deldistx;
	}
	else
	{
		rays->stepx = 1;
		rays->sdistx = (rays->mx + 1.0 - game->player.pos.x) * rays->deldistx;
	}
	if (rays->ray_dir_y < 0)
	{
		rays->stepy = -1;
		rays->sdisty = (game->player.pos.y - rays->my) * rays->deldisty;
	}
	else
	{
		rays->stepy = 1;
		rays->sdisty = (rays->my + 1.0 - game->player.pos.y) * rays->deldisty;
	}
}

void hit_loop(t_game *game, t_rays *rays)
{
	while(rays->hit == 0)
	{
		if (rays->sdistx < rays->sdisty)
		{
			rays->sdistx += rays->deldistx;
			rays->mx += rays->stepx;
			rays->side = 0;
		}
		else
		{
			rays->sdisty += rays->deldisty;
			rays->my += rays->stepy;
			rays->side = 1;
		}
		if ((rays->mx < 0 || rays->mx > game->map.map_w - 1))
		{
			if (rays->mx < 0)
				rays->mx += 1;
			else 
				rays->mx -= 1;
			rays->hit = 1;
		}
		else if (rays->my < 0 || rays->my > game->map.map_h - 1)
		{
			if (rays->my < 0)
				rays->my += 1;
			else 
				rays->my -= 1;
			rays->hit = 1;
		}
		else if (game->map.map[rays->my][rays->mx] == 1)
		{
			rays->hit = 1;
		}
	}
}

void walldist(t_rays *rays)
{
	if (rays->side == 0)
	{
		rays->walldist = (rays->sdistx - rays->deldistx) / 10;
	}
	else
	{
		rays->walldist = (rays->sdisty - rays->deldisty) / 10;
	}
}

void	raycasting(t_game *game)
{
	int x = 0;
	t_rays *rays = (t_rays *)malloc(sizeof(t_rays));

	while (x < WIDTH/2)
	{
		init_rays(game, rays, x);
		step_and_dist(game, rays);
		hit_loop(game, rays);
		walldist(rays);
		
		t_point hitp;
		t_point pos;
		t_point wallhit;
		
		t_point ray;
		ray.x = rays->ray_dir_x;
		ray.y = rays->ray_dir_y;
		
		wallhit.x = game->player.pos.x + rays->walldist * 10 * rays->ray_dir_x;
		wallhit.y = game->player.pos.y + rays->walldist * 10 * rays->ray_dir_y;
		
		hitp.x = (game->player.pos.x + rays->walldist * 10 * rays->ray_dir_x) * game->map.scale;
		hitp.y = (game->player.pos.y + rays->walldist *10 * rays->ray_dir_y) * game->map.scale;
		
		pos.x = game->player.pos.x * game->map.scale;
		pos.y = game->player.pos.y * game->map.scale;
		
		if (x %15 == 0)
			draw_line(&pos, &hitp, game, 0xFF0000FF);
		
		int colour = get_colour(pos, hitp, rays->side);
		int lineheight = HEIGHT / rays->walldist;
		
		int start = -lineheight / 2 + HEIGHT / 2;
		if (colour != NO && start < 0)
			start = 0;
		int end = lineheight / 2 + HEIGHT / 2;		
		if (colour != NO && end >= HEIGHT)
			end = HEIGHT - 1;
		if (colour == NO)
			draw_tex(game, x, start, end, wallhit, ray, rays->side);
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
