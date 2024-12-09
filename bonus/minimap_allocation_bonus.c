/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_allocation_bonus.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pstrohal <pstrohal@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 20:37:30 by pstrohal          #+#    #+#             */
/*   Updated: 2024/11/14 17:07:51 by pstrohal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub_bonus.h"

// works in combination with draw_circle in a simple algorithm
void	circle_points(t_circle_help *c, mlx_image_t *img, uint32_t col)
{
	if (c->x == 0)
	{
		mlx_put_pixel(img, c->xcenter, c->ycenter + c->y, col);
		mlx_put_pixel(img, c->xcenter, c->ycenter - c->y, col);
		mlx_put_pixel(img, c->xcenter + c->y, c->ycenter, col);
		mlx_put_pixel(img, c->xcenter - c->y, c->ycenter, col);
	}
	else if (c->x == c->y)
	{
		mlx_put_pixel(img, c->xcenter + c->x, c->ycenter + c->y, col);
		mlx_put_pixel(img, c->xcenter - c->x, c->ycenter + c->y, col);
		mlx_put_pixel(img, c->xcenter + c->x, c->ycenter - c->y, col);
		mlx_put_pixel(img, c->xcenter - c->x, c->ycenter - c->y, col);
	}
	else if (c->x < c->y)
	{
		mlx_put_pixel(img, c->xcenter - c->x, c->ycenter + c->y, col);
		mlx_put_pixel(img, c->xcenter + c->x, c->ycenter - c->y, col);
		mlx_put_pixel(img, c->xcenter - c->x, c->ycenter - c->y, col);
		mlx_put_pixel(img, c->xcenter + c->x, c->ycenter + c->y, col);
		mlx_put_pixel(img, c->xcenter + c->y, c->ycenter + c->x, col);
		mlx_put_pixel(img, c->xcenter - c->y, c->ycenter + c->x, col);
		mlx_put_pixel(img, c->xcenter + c->y, c->ycenter - c->x, col);
		mlx_put_pixel(img, c->xcenter - c->y, c->ycenter - c->x, col);
	}
}

// draws a circle on the imgage pointed to by img in color col with
// a specified radius. if the radius is bigger than would fit on img
// it will draw the biggest possible one.
void	draw_circle(mlx_image_t *img, uint32_t col, uint32_t radius)
{
	t_circle_help	c;

	c.xcenter = img->height / 2;
	c.ycenter = img->width / 2;
	if (radius <= img->width / 2 - 1)
		c.r = radius;
	else
		c.r = img->width / 2 - 1;
	c.y = c.r;
	c.p = (5 - c.r * 4) / 4;
	c.x = 0;
	circle_points(&c, img, col);
	while (c.x < c.y)
	{
		c.x++;
		if (c.p < 0)
			c.p += 2 * c.x + 1;
		else
		{
			c.y--;
			c.p += 2 * (c.x - c.y) + 1;
		}
		circle_points(&c, img, col);
	}
}

// fils the outside of the img with a circle drawn on with all full rgba(white).
void	fill_outside_circle(mlx_image_t *img)
{
	u_int32_t	x;
	u_int32_t	y;

	y = -1;
	while (++y < img->height)
	{
		x = -1;
		while (++x < img->width / 2 && colour(&img->pixels[((y * img->width)
						+ x) * 4]) != 0xFFFFFFFF)
			mlx_put_pixel(img, x, y, 0xFFFFFFFF);
		x = img->width;
		while (--x > img->width / 2 && colour(&img->pixels[((y * img->width)
						+ x) * 4]) != 0xFFFFFFFF)
			mlx_put_pixel(img, x, y, 0xFFFFFFFF);
	}
}

// allocates a new image that is used to map the minimap to a circular form.
void	minimap_init(t_game *game)
{
	game->circle = mlx_new_image(game->mlx, (uint32_t)MINIMAP_H,
			(uint32_t)MINIMAP_H);
	if (!game->circle)
		error_print("Oh shit circle img failed!");
	draw_circle(game->circle, 0xFFFFFFFF, game->circle->width / 2 - 1);
	fill_outside_circle(game->circle);
}
