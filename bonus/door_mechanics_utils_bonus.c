/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door_mechanics_utils_bonus.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pstrohal <pstrohal@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 20:59:43 by pstrohal          #+#    #+#             */
/*   Updated: 2024/11/14 17:18:11 by pstrohal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub_bonus.h"

void	set_dir(t_door *d, t_door *p, t_db i, t_db j)
{
	d->dir = i;
	p->dir = j;
}

void	set_status(t_door *d, t_door *p, int i)
{
	d->status = i;
	p->status = i;

}

void	set_status_progress(t_door *d, int status, t_db progress)
{
	t_game	*game;

	game = game_pointer(0, NULL);
	d->status = status;
	d->progress = progress;
	game->map.map[d->map_y][d->map_x] = status;
}

int	intersection_with_door(t_game *game, t_point pos, t_point p)
{
	t_door	*d;
	t_point	tmp;
	t_list	*doors;

	doors = game->map.dstuff.doors;
	tmp = vector(pos, p);
	p = point_x_vector(pos, 3, tmp);
	while (doors)
	{
		d = (t_door *)doors->content;
		tmp = segment_intersection(pos, p, d->p1, d->p2);
		if (tmp.x && tmp.y)
			return (1);
		doors = doors->next;
	}
	return (0);
}

// returns the angle between vector a and vector b.
// a and b dont need to be normalized.
double	vector_angle(t_point a, t_point b)
{
	double	scalar_product;
	double	magnitude_a;
	double	magnitude_b;
	double	angle;

	scalar_product = a.x * b.x + a.y * b.y;
	magnitude_a = sqrt(a.x * a.x + a.y * a.y);
	magnitude_b = sqrt(b.x * b.x + b.y * b.y);
	angle = acos(scalar_product / (magnitude_a * magnitude_b));
	return (angle);
}
