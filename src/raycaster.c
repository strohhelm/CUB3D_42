/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: timschmi <timschmi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 18:38:45 by timschmi          #+#    #+#             */
/*   Updated: 2024/10/01 15:41:07 by timschmi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

int return_orientation(int one, int two, int side)
{
	if (side == 0)
		return(one);
	else
		return(two);
}

int	get_direction(t_point pos, t_point hit, int side)
{
	if (pos.x <= hit.x && pos.y >= hit.y)
		return(return_orientation(EAST, NORTH, side));
	else if (pos.x >= hit.x && pos.y >= hit.y)
		return(return_orientation(WEST, NORTH, side));
	else if (pos.x >= hit.x && pos.y <= hit.y)
		return(return_orientation(WEST, SOUTH, side));
	else if ((pos.x <= hit.x && pos.y <= hit.y))
		return(return_orientation(EAST, SOUTH, side));
	else
		return (0);
}

void	draw_tex(t_game *game, int x, t_rays *ray)
{
	double	step;
	int		i;
	t_point	tex;
	uint8_t	*tex_pos;
	uint8_t	*img_pos;
	int		arr_pos;
	int		pic_pos;
	uint32_t test;

	i = 0;
	step = 1.0 * game->map.textures[ray->dir]->height / ray->lineheight;
	if (ray->dir == NORTH || ray->dir == SOUTH)
		tex.x = game->map.textures[ray->dir]->width * fmod(ray->wallhit.x, 1.0);
	else
		tex.x = game->map.textures[ray->dir]->width * fmod(ray->wallhit.y, 1.0);
	if (ray->dir == WEST || ray->dir == SOUTH)
		tex.x = game->map.textures[ray->dir]->width - tex.x;
	while (i <= ray->lineheight)
	{
		if (!(ray->start + i <= 0 || ray->start + i >= HEIGHT))
		{
			tex.y = i * step;
			arr_pos = ((int)tex.y * game->map.textures[ray->dir]->width
					+ (int)tex.x)
				* game->map.textures[ray->dir]->bytes_per_pixel;
			tex_pos = &game->map.textures[ray->dir]->pixels[arr_pos];
			pic_pos = ((ray->start + i) * game->img->width + x)
				* game->map.textures[ray->dir]->bytes_per_pixel;
			img_pos = &game->img->pixels[pic_pos];
			ft_memmove(&test, tex_pos,
				game->map.textures[ray->dir]->bytes_per_pixel);
			if (test > 0)
				ft_memmove(img_pos, tex_pos,
					game->map.textures[ray->dir]->bytes_per_pixel);
		}
		i++;
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
		// if ((ray->mx < 0 || ray->mx > game->map.map_w - 1))
		// {
		// 	if (ray->mx < 0)
		// 		ray->mx += 1;
		// 	else
		// 		ray->mx -= 1;
		// 	ray->hit = 1;
		// }
		// else if (ray->my < 0 || ray->my > game->map.map_h - 1)
		// {
		// 	if (ray->my < 0)
		// 		ray->my += 1;
		// 	else
		// 		ray->my -= 1;
		// 	ray->hit = 1;
		// }
		if (game->map.map[ray->my][ray->mx] == 1)
			ray->hit = 1;
	}
}

void	walldist(t_rays *ray)
{
	if (ray->side == 0)
	{
		ray->walldist = (ray->sdistx - ray->deldistx) / 10;
	}
	else
	{
		ray->walldist = (ray->sdisty - ray->deldisty) / 10;
	}
}

void	render_calc(t_game *game, t_rays *ray)
{
	ray->wallhit.x = game->player.pos.x + ray->walldist * 10 * ray->ray_dir_x;
	ray->wallhit.y = game->player.pos.y + ray->walldist * 10 * ray->ray_dir_y;
	ray->hitp.x = (game->player.pos.x + ray->walldist * 10 * ray->ray_dir_x)
		* game->map.scale;
	ray->hitp.y = (game->player.pos.y + ray->walldist * 10 * ray->ray_dir_y)
		* game->map.scale;
	ray->pos.x = game->player.pos.x * game->map.scale;
	ray->pos.y = game->player.pos.y * game->map.scale;
	ray->lineheight = HEIGHT / ray->walldist;
	ray->start = -ray->lineheight / 2 + HEIGHT / 2;
	ray->end = ray->lineheight / 2 + HEIGHT / 2;
	ray->dir = get_direction(ray->pos, ray->hitp, ray->side);
}

void	raycasting(t_game *game)
{
	int		x;
	t_rays	*ray;

	x = 0;
	ray = (t_rays *)malloc(sizeof(t_rays));
	while (x < WIDTH)
	{
		init_rays(game, ray, x);
		step_and_dist(game, ray);
		hit_loop(game, ray);
		walldist(ray);
		render_calc(game, ray);
		draw_tex(game, x, ray);
		x++;
	}
	free(ray);
}
