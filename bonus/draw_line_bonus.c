/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: timschmi <timschmi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 15:32:14 by pstrohal          #+#    #+#             */
/*   Updated: 2024/11/13 17:38:55 by timschmi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub_bonus.h"

void	draw_line_x(mlx_image_t *img, t_pixel_line z, int w, int h)
{
	z.a = 2 * z.ydiff;
	z.b = z.a - 2 * z.xdiff;
	z.p = z.a - z.xdiff;
	while (z.xdiff > 0)
	{
		if (z.p_a.x < z.p_b.x)
			z.p_t.x++;
		else
			z.p_t.x--;
		if (z.p < 0)
			z.p += z.a;
		else
		{
			if (z.p_a.y > z.p_b.y)
				z.p_t.y--;
			else
				z.p_t.y++;
			z.p += z.b;
		}
		if (z.p_t.x >= 0 && z.p_t.y >= 0 && z.p_t.x < w && z.p_t.y < h)
			mlx_put_pixel(img, z.p_t.x, z.p_t.y, z.col);
		z.xdiff--;
	}
}

void	draw_line_y(mlx_image_t *img, t_pixel_line z, int w, int h)
{
	z.a = 2 * z.xdiff;
	z.b = z.a - 2 * z.ydiff;
	z.p = z.a - z.ydiff;
	while (z.ydiff > 0)
	{
		if (z.p_a.y < z.p_b.y)
			z.p_t.y++;
		else
			z.p_t.y--;
		if (z.p < 0)
			z.p += z.a;
		else
		{
			if (z.p_a.x > z.p_b.x)
				z.p_t.x--;
			else
				z.p_t.x++;
			z.p += z.b;
		}
		if (z.p_t.x >= 0 && z.p_t.y >= 0 && z.p_t.x < w && z.p_t.y < h)
			mlx_put_pixel(img, z.p_t.x, z.p_t.y, z.col);
		z.ydiff--;
	}
}

// returns the absolute value of the difference between a and b.
int	ft_absolute(int a, int b)
{
	int	nb;

	nb = a - b;
	return ((nb >= 0) * nb + (nb < 0) * -1 * nb);
}

// needs mlx_img pointer and colour input.
// draws line in berensham's line algorithm.
void	draw_line(t_point *p_a, t_point *p_b, mlx_image_t *img, int color)
{
	t_pixel_line	z;
	t_point			a;
	t_point			b;

	a.x = p_a->x;
	a.y = p_a->y;
	b.x = p_b->x;
	b.y = p_b->y;
	z.p_a = a;
	z.p_b = b;
	z.p_t = a;
	z.col = color;
	z.xdiff = ft_absolute(a.x, b.x);
	z.ydiff = ft_absolute(a.y, b.y);
	if (z.xdiff >= z.ydiff)
		draw_line_x(img, z, WIDTH, HEIGHT);
	if (z.ydiff > z.xdiff)
		draw_line_y(img, z, WIDTH, HEIGHT);
	return ;
}
