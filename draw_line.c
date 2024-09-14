/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pstrohal <pstrohal@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 15:32:14 by pstrohal          #+#    #+#             */
/*   Updated: 2024/09/14 17:39:24 by pstrohal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

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

//needs mlx_img pointer and colour input;
void	draw_line(t_point *p_a, t_point *p_b, t_player *size)
{
	t_pixel_line	z;

	z.p_a = *p_a;
	z.p_b = *p_b;
	z.p_t = *p_a;
	z.col = size->colour;
	z.xdiff = ft_absolute(p_a->x, p_b->x);
	z.ydiff = ft_absolute(p_a->y, p_b->y);
	if (z.xdiff >= z.ydiff)
		draw_line_x(size->img, z, size->width, size->height);
	if (z.ydiff > z.xdiff)
		draw_line_y(size->img, z, size->width, size->height);
	return ;
}
