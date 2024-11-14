/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_utils_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pstrohal <pstrohal@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 16:50:12 by pstrohal          #+#    #+#             */
/*   Updated: 2024/11/14 16:56:16 by pstrohal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub_bonus.h"

void	draw_minimap_rays(t_game *game, t_rays *ray)
{
	t_drawhelp	t;

	t.scale = 0.0;
	t.sc = MINIMAP_H / game->scale;
	t.r = game->circle->width / 2 - 3;
	t.a.x = game->minimap->height / 2.0;
	t.a.y = game->minimap->height / 2.0;
	minimap_door_hit(game, ray->wallhit, &t.b);
	t.b = vector(game->player.pos, t.b);
	if (t.b.x != ray->minimap_hit.x && t.b.y != ray->minimap_hit.y)
		ray->minimap_hit = t.b;
	t.b = point_x_vector(t.a, t.sc, ray->minimap_hit);
	t.dist = dist_points(t.a, t.b);
	if (t.dist > t.r)
	{
		t.scale = t.r / t.dist;
		t.b.x = t.a.x + (t.b.x - t.a.x) * t.scale;
		t.b.y = t.a.y + (t.b.y - t.a.y) * t.scale;
	}
	draw_line(&t.a, &t.b, game->minimap, game->map.ceiling);
}

// changes all pixel outside of the circle drawn on the cicle img 
// to transparent, effectively cutting a circle out of the minimap square.
void	cut_minimap(t_game *game, t_minimap *m)
{
	m->x = 0.0;
	m->y = 0.0;
	m->h = 0;
	while (m->h < m->printh)
	{
		m->y = m->h * m->step;
		m->w = 0;
		while (m->w < m->printh)
		{
			m->x = m->w * m->step;
			if (colour(&game->circle->pixels[(((m->h) * game->circle->width)
							+ m->w) * 4]))
				mlx_put_pixel(game->minimap, m->w, m->h, 0x00000000);
			m->w++;
		}
		m->h++;
	}
}
