/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door_mechanics_utils_bonus.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pstrohal <pstrohal@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 20:59:43 by pstrohal          #+#    #+#             */
/*   Updated: 2024/11/09 21:01:24 by pstrohal         ###   ########.fr       */
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

void set_status_progress(t_door *d, int status, db progress)
{
	d->status = status;
	d->progress = progress;
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