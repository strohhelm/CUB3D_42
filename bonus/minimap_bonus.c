/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: timschmi <timschmi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 20:09:08 by pstrohal          #+#    #+#             */
/*   Updated: 2024/11/14 17:32:34 by timschmi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub_bonus.h"

// initializes the minimap variables and scales depending on user input.
void	init_minimap(t_game *game, t_minimap *m)
{
	if (mlx_is_key_down(game->mlx, MLX_KEY_UP))
		game->scale += 0.1;
	else if (mlx_is_key_down(game->mlx, MLX_KEY_DOWN))
		game->scale -= 0.1;
	m->x = 0.0;
	m->y = 0.0;
	m->wall = 0;
	m->floor = 0;
	m->h = 0;
	m->printh = MINIMAP_H;
	m->step = game->scale / (double)m->printh;
	m->min = MINIMAP_H / 2.0 - 5.0;
	m->max = MINIMAP_H / 2.0 + 5.0;
}

// draws a pixel on the minimap img, according to themap given in the inputfile.
void	check_pixel(t_game *game, t_minimap *m)
{
	if ((int)m->pos.x < game->map.map_w && (int)m->pos.y < game->map.map_h
		&& (int)m->pos.x >= 0 && (int)m->pos.y >= 0)
	{
		if (m->w > m->min && m->w < m->max && m->h > m->min && m->h < m->max)
			mlx_put_pixel(game->minimap, m->w, m->h, game->map.ceiling);
		else if (game->map.map[(int)m->pos.y][(int)m->pos.x] == 1
				|| game->map.map[(int)m->pos.y][(int)m->pos.x] == -1)
			mlx_put_pixel(game->minimap, m->w, m->h, m->wall);
		else if (game->map.map[(int)m->pos.y][(int)m->pos.x] != 1)
			mlx_put_pixel(game->minimap, m->w, m->h, m->floor);
	}
}

void	init_drawhelp(t_game *game, t_drawhelp *d, t_ai *e)
{
	d->a.x = game->minimap->height / 2.0;
	d->a.y = game->minimap->height / 2.0;
	d->v = vector(game->player.pos, e->pos);
	d->sc = MINIMAP_H / game->scale;
	d->b = point_x_vector(d->a, d->sc, d->v);
	d->draw_x = (int)d->b.x - d->printw / 2;
	d->draw_y = (int)d->b.y - d->printw / 2;
}

void	draw_enemies(t_game *game)
{
	t_ai		*enemies;
	t_drawhelp	d;

	enemies = game->e;
	d.printw = MINIMAP_H / game->scale / 5;
	while (enemies)
	{
		init_drawhelp(game, &d, enemies);
		d.y = -1;
		while (++d.y < d.printw)
		{
			d.x = -1;
			while (++d.x < d.printw)
			{
				if (d.draw_x + d.x > 0 && d.draw_x + d.x < MINIMAP_H
					&& d.draw_y + d.y > 0 && d.draw_y + d.y
					< MINIMAP_H && enemies->state == ALIVE)
				{
					mlx_put_pixel(game->minimap, d.draw_x + d.x, d.draw_y + d.y,
						0xFF0000FF);
				}
			}
		}
		enemies = enemies->next;
	}
}

// loops through each pixel of the minimap and draws a pixel.
void	minimap(t_game *game)
{
	t_minimap	m;

	init_minimap(game, &m);
	change_colour(game->map.ceiling, &m.wall, &m.floor);
	while (m.h < m.printh)
	{
		m.y = m.h * m.step;
		m.w = 0;
		while (m.w < m.printh)
		{
			m.x = m.w * m.step;
			m.pos.y = game->player.pos.y - game->scale / 2 + m.y;
			m.pos.x = game->player.pos.x - game->scale / 2 + m.x;
			mlx_put_pixel(game->minimap, m.w, m.h, m.wall);
			check_pixel(game, &m);
			m.w++;
		}
		m.h++;
	}
	draw_minimap_doors(game, m.wall);
	draw_enemies(game);
	cut_minimap(game, &m);
}
