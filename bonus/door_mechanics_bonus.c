/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door_mechanics_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pstrohal <pstrohal@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 15:27:28 by pstrohal          #+#    #+#             */
/*   Updated: 2024/11/09 17:47:09 by pstrohal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub_bonus.h"

void	set_dir(t_door *d, t_door *p, db i, db j)
{
	d->dir = i;
	p->dir = j;
}
void	set_status(t_door *d, t_door *p, int i)
{
	d->status = i;
	p->status = i;
}

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
void set_status_progress(t_door *d, int status, db progress)
{
	d->status = status;
	d->progress = progress;
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
int	intersection_with_door(t_game *game, t_point p)
{
	t_door	*d;
	t_point	tmp;
	t_list	*doors;
	
	doors = game->map.dstuff.doors;
	tmp = vector(game->player.pos, p);
	p = point_x_vector(game->player.pos, 3, tmp);
	while (doors)
	{
		d = (t_door *)doors->content;
		tmp = segment_intersection(game->player.pos, p, d->p1, d->p2);
		if (tmp.x && tmp.y)
			return (1);
		doors = doors->next;
	}
	return (0);
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
			{
				*intersect = tmp;
			}
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
	t_point	mapa;
	t_point	mapb;
	t_list	*doors;
	
	doors = game->map.dstuff.doors;
	x.x = game->minimap->height / 2.0;
	x.y = game->minimap->height / 2.0;
	while (doors)
	{
		d = (t_door *)doors->content;
		a = vector(game->player.pos, d->p1);
		b = vector(game->player.pos, d->p2);
		mapa = point_x_vector(x, MINIMAP_H / game->scale, a);
		mapb = point_x_vector(x, MINIMAP_H / game->scale, b);
		if (mapa.x <= game->minimap->width && mapa.x >= 0 
			&&	mapb.x <= game->minimap->width && mapb.x >= 0
			&& mapa.y <= game->minimap->height && mapa.y >= 0
			&& mapb.y <= game->minimap->height && mapb.y >= 0)
			draw_line(&mapa, &mapb, game->minimap, colour);
		doors = doors->next;
	}
}
