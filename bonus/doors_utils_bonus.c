/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doors_utils_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pstrohal <pstrohal@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 16:24:52 by pstrohal          #+#    #+#             */
/*   Updated: 2024/11/04 16:01:29 by pstrohal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub_bonus.h"

t_point	intersection(t_point a, t_point b, t_point c, t_point d)
{
	t_point	s;
	double t;
	double	denominator;

	s.x = 0.0;
	s.y = 0.0;
	denominator = ((a.x - b.x) * (c.y - d.y) - (a.y - b.y) * (c.x - d.x));
	if (!denominator)
		return(s);
	else
	{
		t = ((a.x - c.x) * (c.y - d.y) - (a.y - c.y) * (c.x - d.x)) / denominator;
	}
	s.x = a.x + t * (b.x - a.x);
	s.y = a.y + t * (b.y - a.y);
	return (s);
}


t_point	vector_between_two_points(t_point a, t_point b)
{
	t_point vector;

	vector.x = b.x - a.x;
	vector.y = b.y - a.y;
	return (vector);
}

double	dist_between_two_points(t_point a, t_point b)
{
	double	dist;
	t_point	vector;
	
	vector = vector_between_two_points(a, b);
	dist = sqrt(vector.x * vector.x + vector.y * vector.y);
	return (dist);
}


t_point	get_new_point(t_point p, t_point vector)
{
	t_point result;

	result.x = p.x + vector.x;
	result.y = p.y + vector.y;
	return (result);
}

t_point	get_point_plus_x_times_vector(t_point p, double x, t_point v)
{
	p.x = p.x + x * v.x;
	p.y = p.y + x * v.y;
	return(p);
}