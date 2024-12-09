/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pstrohal <pstrohal@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 18:38:45 by timschmi          #+#    #+#             */
/*   Updated: 2024/11/14 16:49:45 by pstrohal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub_bonus.h"

void	raycasting(t_game *game)
{
	int	x;

	x = 0;
	while (x < WIDTH)
	{
		init_rays(game, &game->ray, x);
		step_and_dist(game, &game->ray);
		hit_loop(game, &game->ray);
		render_calc(game, &game->ray);
		game->ray.start -= game->y;
		draw_tex(game, x, &game->ray);
		if (x % 50 == 0)
			draw_minimap_rays(game, &game->ray);
		game->dist_arr[x] = game->ray.walldist;
		x++;
	}
}

void	init_rays(t_game *game, t_rays *ray, int x)
{
	ray->camx = 2 * x / (double)(WIDTH)-1;
	ray->ray_dir_x = game->player.dir.x + game->player.scr.x * ray->camx;
	ray->ray_dir_y = game->player.dir.y + game->player.scr.y * ray->camx;
	ray->mx = (int)(game->player.pos.x);
	ray->my = (int)(game->player.pos.y);
	ray->deldistx = fabs(1 / ray->ray_dir_x);
	ray->deldisty = fabs(1 / ray->ray_dir_y);
	ray->hit = 0;
}

void	step_and_dist(t_game *game, t_rays *ray)
{
	if (ray->ray_dir_x < 0)
	{
		ray->stepx = -1;
		ray->sdistx = (game->player.pos.x - ray->mx) * ray->deldistx;
	}
	else
	{
		ray->stepx = 1;
		ray->sdistx = (ray->mx + 1.0 - game->player.pos.x) * ray->deldistx;
	}
	if (ray->ray_dir_y < 0)
	{
		ray->stepy = -1;
		ray->sdisty = (game->player.pos.y - ray->my) * ray->deldisty;
	}
	else
	{
		ray->stepy = 1;
		ray->sdisty = (ray->my + 1.0 - game->player.pos.y) * ray->deldisty;
	}
}

void	ray_overflow(t_game *game, t_rays *ray)
{
	if ((ray->mx < 0 || ray->mx > game->map.map_w - 1))
	{
		if (ray->mx < 0)
			ray->mx += 1;
		else
			ray->mx -= 1;
		ray->hit = 1;
	}
	else if (ray->my < 0 || ray->my > game->map.map_h - 1)
	{
		if (ray->my < 0)
			ray->my += 1;
		else
			ray->my -= 1;
		ray->hit = 1;
	}
}

void	hit_loop(t_game *game, t_rays *ray)
{
	while (ray->hit == 0)
	{
		if (ray->sdistx < ray->sdisty)
		{
			ray->sdistx += ray->deldistx;
			ray->mx += ray->stepx;
			ray->side = 0;
		}
		else
		{
			ray->sdisty += ray->deldisty;
			ray->my += ray->stepy;
			ray->side = 1;
		}
		ray_overflow(game, ray);
		if (game->map.map[ray->my][ray->mx] == 1)
			ray->hit = 1;
	}
}
