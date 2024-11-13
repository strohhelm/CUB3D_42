/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doors_utils_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: timschmi <timschmi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 16:24:52 by pstrohal          #+#    #+#             */
/*   Updated: 2024/11/13 17:39:03 by timschmi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub_bonus.h"

// returns the point of intersection between ray from a through b
// and line segment CD.
// If there is none, returns point (0.0 | 0.0)
t_point	intersection(t_point a, t_point b, t_point c, t_point d)
{
	t_point	s;
	double	t;
	double	u;
	double	denom;

	s.x = 0.0;
	s.y = 0.0;
	denom = ((a.x - b.x) * (c.y - d.y) - (a.y - b.y) * (c.x - d.x));
	if (!denom)
		return (s);
	else
	{
		t = ((a.x - c.x) * (c.y - d.y) - (a.y - c.y) * (c.x - d.x)) / denom;
		u = -((a.x - b.x) * (a.y - c.y) - (a.y - b.y) * (a.x - c.x)) / denom;
	}
	if (t > 0 && u > 0 && u < 1)
	{
		s.x = a.x + t * (b.x - a.x);
		s.y = a.y + t * (b.y - a.y);
	}
	return (s);
}
// returns the point of intersection between line segment AB
// and line segment CD.
// If there is none, returns point (0.0 | 0.0)
t_point	segment_intersection(t_point a, t_point b, t_point c, t_point d)
{
	t_point	s;
	double	t;
	double	u;
	double	denom;

	s.x = 0.0;
	s.y = 0.0;
	denom = ((a.x - b.x) * (c.y - d.y) - (a.y - b.y) * (c.x - d.x));
	if (!denom)
		return (s);
	else
	{
		t = ((a.x - c.x) * (c.y - d.y) - (a.y - c.y) * (c.x - d.x)) / denom;
		u = -((a.x - b.x) * (a.y - c.y) - (a.y - b.y) * (a.x - c.x)) / denom;
	}
	if (t > 0 && t <= 1 && u > 0 && u <= 1)
	{
		s.x = a.x + t * (b.x - a.x);
		s.y = a.y + t * (b.y - a.y);
	}
	return (s);
}

// returns the vector between point a and point b
t_point	vector(t_point a, t_point b)
{
	t_point	vector;

	vector.x = b.x - a.x;
	vector.y = b.y - a.y;
	return (vector);
}

// returns the distance bewteen point a and point b
double	dist_points(t_point a, t_point b)
{
	double	dist;
	t_point	v;

	v = vector(a, b);
	dist = sqrt(v.x * v.x + v.y * v.y);
	return (dist);
}

// returns the point p multiplied by x times vector v
t_point	point_x_vector(t_point p, double x, t_point v)
{
	p.x = p.x + x * v.x;
	p.y = p.y + x * v.y;
	return (p);
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
