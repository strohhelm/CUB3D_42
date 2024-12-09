/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast_textures_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pstrohal <pstrohal@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 15:44:50 by timschmi          #+#    #+#             */
/*   Updated: 2024/11/14 17:17:51 by pstrohal         ###   ########.fr       */
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

void	tex_line(t_game *game, t_rays *ray, t_texture *tex, int x)
{
	if (x == (int)WIDTH / 2 && ray->start + tex->i == (HEIGHT / 2)
		&& game->player.attack == 1)
	{
		draw_on_tex(game, tex, ray->dir);
	}
	if (game->map.indiv[tex->index]
		&& game->map.indiv[tex->index]->arr[ray->dir] == 1)
		tex->tex_pos = &game->map.indiv[tex->index]->side[ray->dir]
			.pixels[tex->arr_pos];
	else
		tex->tex_pos = &game->map.textures[ray->dir]->pixels[tex->arr_pos];
	tex->pic_pos = ((ray->start + tex->i) * game->img->width + x)
		* game->map.textures[ray->dir]->bytes_per_pixel;
	tex->img_pos = &game->img->pixels[tex->pic_pos];
	if (tex->tex_pos)
		tex->test = *(u_int32_t *)tex->tex_pos;
	if (tex->test)
	{
		tex->test = darken_colour(tex->test, ray->walldist * 15);
		*(uint32_t *)tex->img_pos = tex->test;
	}
}

void	tex_loop(t_game *game, t_rays *ray, t_texture *tex, int x)
{
	tex->i = 0;
	tex->w = (uint)(ray->hitp.x + EPSILON);
	tex->y = (uint)(ray->hitp.y + EPSILON);
	if (ray->dir == NORTH)
		tex->index = (tex->y - 1) * (uint)game->map.map_w + tex->w;
	else if (ray->dir == WEST)
		tex->index = tex->y * game->map.map_w + (tex->w - 1);
	else
		tex->index = tex->y * game->map.map_w + tex->w;
	while (tex->i < ray->lineheight)
	{
		if (!(ray->start + tex->i < 0 || ray->start + tex->i >= HEIGHT))
		{
			tex->tex.y = (double)tex->i * tex->step;
			tex->arr_pos = ((long)tex->tex.y
					* game->map.textures[ray->dir]->width + (uint)tex->tex.x)
				* 4;
			tex_line(game, ray, tex, x);
		}
		tex->i++;
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
