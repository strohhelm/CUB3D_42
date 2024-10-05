/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast_textures_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pstrohal <pstrohal@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 15:44:50 by timschmi          #+#    #+#             */
/*   Updated: 2024/10/05 23:32:33 by pstrohal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub_bonus.h"

void	draw_tex(t_game *game, int x, t_rays *ray)
{
	t_texture	*tex;

	tex = &ray->tex;
	tex->step = 1.0 * game->map.textures[ray->dir]->height / ray->lineheight;
	if (ray->dir == NORTH || ray->dir == SOUTH)
		tex->tex.x = game->map.textures[ray->dir]->width * fmod(ray->wallhit.x,
				1.0);
	else
		tex->tex.x = game->map.textures[ray->dir]->width * fmod(ray->wallhit.y,
				1.0);
	if (ray->dir == WEST || ray->dir == SOUTH)
		tex->tex.x = game->map.textures[ray->dir]->width - tex->tex.x;
	tex_loop(game, ray, tex, x);
}

void	tex_loop(t_game *game, t_rays *ray, t_texture *tex, int x)
{
	int	i;

	i = 0;
	while (i < ray->lineheight)
	{
		if (!(ray->start + i < 0 || ray->start + i >= HEIGHT))
		{
			tex->tex.y = i * tex->step;
			tex->arr_pos = ((int)tex->tex.y
					* game->map.textures[ray->dir]->width + (int)tex->tex.x)
				* game->map.textures[ray->dir]->bytes_per_pixel;
			tex->tex_pos = &game->map.textures[ray->dir]->pixels[tex->arr_pos];
			tex->pic_pos = ((ray->start + i) * game->img->width + x)
				* game->map.textures[ray->dir]->bytes_per_pixel;
			tex->img_pos = &game->img->pixels[tex->pic_pos];
			ft_memmove(&tex->test, tex->tex_pos,
				game->map.textures[ray->dir]->bytes_per_pixel);
			if (tex->test > 0)
				ft_memmove(tex->img_pos, tex->tex_pos,
					game->map.textures[ray->dir]->bytes_per_pixel);
		}
		i++;
	}
}

int	return_orientation(int one, int two, int side)
{
	if (side == 0)
		return (one);
	else
		return (two);
}

int	get_direction(t_point pos, t_point hit, int side)
{
	if (pos.x <= hit.x && pos.y >= hit.y)
		return (return_orientation(EAST, NORTH, side));
	else if (pos.x >= hit.x && pos.y >= hit.y)
		return (return_orientation(WEST, NORTH, side));
	else if (pos.x >= hit.x && pos.y <= hit.y)
		return (return_orientation(WEST, SOUTH, side));
	else if ((pos.x <= hit.x && pos.y <= hit.y))
		return (return_orientation(EAST, SOUTH, side));
	else
		return (0);
}

void	render_calc(t_game *game, t_rays *ray)
{
	if (ray->side == 0)
		ray->walldist = (ray->sdistx - ray->deldistx) / 10;
	else
		ray->walldist = (ray->sdisty - ray->deldisty) / 10;
	ray->wallhit.x = game->player.pos.x + ray->walldist * 10 * ray->ray_dir_x;
	ray->wallhit.y = game->player.pos.y + ray->walldist * 10 * ray->ray_dir_y;
	ray->hitp.x = ray->walldist * 10 * ray->ray_dir_x;
	ray->hitp.y = ray->walldist * 10 * ray->ray_dir_y;

	ray->pos.x = game->player.pos.x * game->map.scale;
	ray->pos.y = game->player.pos.y * game->map.scale;
	ray->lineheight = HEIGHT / ray->walldist;
	ray->start = -ray->lineheight / 2 + HEIGHT / 2;
	ray->end = ray->lineheight / 2 + HEIGHT / 2;
	ray->dir = get_direction(ray->pos, ray->hitp, ray->side);
}
