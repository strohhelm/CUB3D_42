/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doors_utils2_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pstrohal <pstrohal@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 16:27:42 by pstrohal          #+#    #+#             */
/*   Updated: 2024/11/02 17:09:32 by pstrohal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub_bonus.h"

// distance from line through a and b to point c;
double orth_distance(t_point a, t_point b, t_point c)
{
	double result;
	double	denominator;
	double numerator;
	
	denominator = sqrt(pow(b.y - a.y, 2) + pow(b.x - a.x, 2));
	numerator = (b.y - a.y) * c.x - (b.x - a.x) * c.y + b.x * a.y - b.y * a.x;
	result = fabs(numerator) / denominator;
	return (result);
}

double	dot_prod(t_point a, t_point b)
{
	return (a.x * b.x + a.y * b.y);
}


double magn(t_point a)
{
	return (sqrt(a.x * a.x + a.y * a.y));
}

double angle_between_vectors(t_point a, t_point b)
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
void	set_left_right_vectors(t_game *game, t_doorhelp *hlp, t_door *d)
{
	hlp->p1_dir = left_or_right(game, hlp, d->p1);
	hlp->p2_dir = left_or_right(game, hlp, d->p2);
	hlp->p1_dist = orth_distance(hlp->pos,
				get_new_point(hlp->pos, hlp->dirvector), d->p1);
	hlp->p2_dist = orth_distance(hlp->pos,
				get_new_point(hlp->pos, hlp->dirvector), d->p2);
	if ((hlp->p1_dir == LEFT && hlp->p2_dir == RIGHT)
		|| ((hlp->p1_dir == LEFT && hlp->p2_dir == LEFT)
		&& hlp->p1_dist >= hlp->p2_dist))
	{
		hlp->left_vector = hlp->p1vector;
		hlp->left_d_point = d->p1;
		hlp->right_vector = hlp->p2vector;
		hlp->right_d_point = d->p2;
		hlp->left_angle = hlp->p1_angle;
		hlp->right_angle = hlp->p2_angle;
		hlp->left_dir = hlp->p1_dir;
		hlp->right_dir = hlp->p2_dir;
	}
	else if ((hlp->p1_dir == RIGHT && hlp->p2_dir == LEFT)
		|| ((hlp->p1_dir == RIGHT && hlp->p2_dir == RIGHT)
		&& hlp->p1_dist <= hlp->p2_dist))
	{
		hlp->left_vector = hlp->p2vector;
		hlp->left_d_point = d->p2;
		hlp->right_vector = hlp->p1vector;
		hlp->right_d_point = d->p1;
		hlp->left_angle = hlp->p2_angle;
		hlp->right_angle = hlp->p1_angle;
		hlp->left_dir = hlp->p2_dir;
		hlp->right_dir = hlp->p1_dir;
	}
	else if (hlp->p1_dir == OOPS || hlp->p2_dir == OOPS)
		error_print("OOPS something wrong brother!");
}
