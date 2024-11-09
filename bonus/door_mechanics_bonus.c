/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door_mechanics_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pstrohal <pstrohal@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 15:27:28 by pstrohal          #+#    #+#             */
/*   Updated: 2024/11/09 21:05:22 by pstrohal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub_bonus.h"

void	door_move(t_game *game, t_door *d)
{
	t_list	*doors;
	t_door	*p;
	int		i;
	int		dir;

	if (d)
	{
		dir = left_or_right(d->p1, d->p2, game->player.pos);
		doors = game->map.dstuff.doors;
		i = d->id - 1;
		if (d->id % 2 == 0)
			i = d->id + 1;
		while (i-- > 0 && doors)
			doors = doors->next;
		p = doors->content;
		if (d->status == CLOSED)
		{
			set_dir(d, p, -1.0, 1.0);
			if (!dir)
				set_dir(d, p, 1.0, -1.0);
			set_status(d, p, OPENING);
		}
		else if (d->status == OPEN)
			set_status(d, p, CLOSING);
	}
}

void	rotate_door(t_door *d)
{
	t_point	v;
	t_point	rot;
	double l_r;
	
	l_r = d->dir;
	v = vector(d->p1, d->p2);
	if (d->status == CLOSING)
	{
		d->progress -= 1.0 / FPS;
		l_r = d->dir * -1.0;
		if (d->progress <= 0.0 + 1 / FPS)
			set_status_progress(d, CLOSED, 0.0);
	}
	else if (d->status == OPENING)
	{
		d->progress += 1.0 / FPS;
		if (d->progress >= 1.0 - 1 / FPS)
			set_status_progress(d, OPEN, 1.0);
	}
	rot.x = v.x * cos(ROTATE_AMOUNT * l_r) - v.y * sin(ROTATE_AMOUNT * l_r);
	rot.y = v.x * sin(ROTATE_AMOUNT * l_r) + v.y * cos(ROTATE_AMOUNT * l_r);
	d->p2 = point_x_vector(d->p1, 1.0, rot);
}

void	doors(t_game *game)
{
	t_list	*doors;
	t_door	*d;

	doors = game->map.dstuff.doors;
	while (doors)
	{
		d = (t_door *)doors->content;
		if (d->status == CLOSING || d->status == OPENING)
		{
			rotate_door(d);
		}
		doors = doors->next;
	}
}

void	minimap_door_hit(t_game *game, t_point hit, t_point *intersect)
{
	t_door	*d;
	t_point	tmp;
	t_list	*doors;
	
	doors = game->map.dstuff.doors;
	*intersect = hit;
	while (doors)
	{
		d = (t_door *)doors->content;
		tmp = segment_intersection(game->player.pos, hit, d->p1, d->p2);
		if (tmp.x != 0 && tmp.y != 0)
		{
			if (dist_points(game->player.pos, tmp)
				< dist_points(game->player.pos, *intersect))
				*intersect = tmp;
		}
		doors = doors->next;
	}
}

void	draw_minimap_doors(t_game *game, uint32_t colour)
{
	t_door	*d;
	t_point	x;
	t_point	a;
	t_point	b;
	t_list	*doors;
	
	doors = game->map.dstuff.doors;
	x.x = game->minimap->height / 2.0;
	x.y = game->minimap->height / 2.0;
	while (doors)
	{
		d = (t_door *)doors->content;
		a = vector(game->player.pos, d->p1);
		b = vector(game->player.pos, d->p2);
		a = point_x_vector(x, MINIMAP_H / game->scale, a);
		b = point_x_vector(x, MINIMAP_H / game->scale, b);
		if (a.x <= game->minimap->width && a.x >= 0 
			&&	b.x <= game->minimap->width && b.x >= 0
			&& a.y <= game->minimap->height && a.y >= 0
			&& b.y <= game->minimap->height && b.y >= 0)
			draw_line(&a, &b, game->minimap, colour);
		doors = doors->next;
	}
}
