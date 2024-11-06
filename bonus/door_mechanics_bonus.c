/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door_mechanics_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pstrohal <pstrohal@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 15:27:28 by pstrohal          #+#    #+#             */
/*   Updated: 2024/11/06 18:02:26 by pstrohal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub_bonus.h"

void	door_move(t_door *d)
{
	if (d)
	{
		if (d->status == CLOSED || d->status == CLOSING)
		{
			d->status = OPENING;
		}
		else if (d->status == OPEN || d->status == OPENING)
		{
			d->status = CLOSING;
		}
	}
}

void	rotate_door(t_door *d)
{
	t_point	v;
	t_point	rot;
	double l_r;

	l_r = 1;
	v = vector(d->p1, d->p2);
	if (d->status == CLOSING)
	{
		d->progress -= 1.0 / FPS;
		l_r = -1;
		if (d->progress <= 0.0 + 1 / FPS)
		{
			d->status = CLOSED;
			d->progress = 0.0;
		}
	}
	else if (d->status == OPENING)
	{
		d->progress += 1.0 / FPS;
		if (d->progress >= 1.0 - 1 / FPS)
		{
			d->status = OPEN;
			d->progress = 1.0;
		}
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
			rotate_door(d);
		doors = doors->next;
	}
}
