/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doors_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pstrohal <pstrohal@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 17:21:53 by pstrohal          #+#    #+#             */
/*   Updated: 2024/11/14 15:06:49 by pstrohal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub_bonus.h"

void	init_for_draw_doorline(t_game *game, t_doorhelp *h)
{
	h->doorwidth = dist_points(h->d->p1, h->d->p2);
	h->start = -h->lineheight / 2 + HEIGHT / 2 - game->y;
	h->end = h->lineheight / 2 + HEIGHT / 2;
	h->tex_step = (t_db)h->d->texture->height / (t_db)h->lineheight;
	h->door_x = dist_points(h->d->p1, h->door_intersect);
	h->tex_coords.x = (t_db)h->d->texture->width / (h->doorwidth / h->door_x);
	h->tex_coords.y = 0;
}

// drwaing the texture of the door on the main image on the screen.
// depending on distance and intersection finding the correct texture values.
void	draw_doorline(t_game *game, t_doorhelp *h, int x)
{
	int	i;

	i = -1;
	init_for_draw_doorline(game, h);
	while (++i < h->lineheight)
	{
		if (h->start + i > 0 && h->start + i < HEIGHT)
		{
			h->tex_index = (((int)(h->tex_coords.y) * h->d->texture->width)
					+ (int)(h->tex_coords.x)) * 4;
			h->tex_pos = &h->d->texture->pixels[h->tex_index];
			h->img_index = (((h->start + i) * game->img->width) + x) * 4;
			h->img_pos = &game->img->pixels[h->img_index];
			check_emg(game, h);
			if (h->test)
				*((t_uint *)h->img_pos) = *((t_uint *)h->tex_pos);
		}
		h->tex_coords.y += h->tex_step;
	}
}

// looping through each doorstruct to see if on ray direction is an
// intersection with a doorline, and if so returning the closest one.
void	check_intersect(t_game *game, t_doorhelp *h, t_list *doors, int i)
{
	t_door	*d;
	t_point	tmp;

	h->dist = game->dist_arr[i] + 2.0;
	while (doors)
	{
		d = (t_door *)doors->content;
		tmp = intersection(h->pos, h->screen_x, d->p1, d->p2);
		if (tmp.x && tmp.y)
		{
			h->tmpdist = dist_points(h->pos, tmp);
			h->angle = vector_angle(h->dirvector, vector(h->pos, h->screen_x));
			if (h->angle != 0.0)
				h->tmpdist *= cos(h->angle);
			if (h->tmpdist < h->dist)
			{
				h->dist = h->tmpdist;
				h->door_intersect = tmp;
				h->d = d;
			}
		}
		doors = doors->next;
	}
}

// initializing the helpstruct
void	get_screen(t_game *game, t_player *player, t_doorhelp *h)
{
	int	i;

	h->sl.x = player->pos.x - player->scr.x + player->dir.x;
	h->sl.y = player->pos.y - player->scr.y + player->dir.y;
	h->sr.x = player->pos.x + player->scr.x + player->dir.x;
	h->sr.y = player->pos.y + player->scr.y + player->dir.y;
	h->pos = player->pos;
	h->screenvector = vector(h->sl, h->sr);
	h->stepvector.x = h->screenvector.x / (t_db)WIDTH;
	h->stepvector.y = h->screenvector.y / (t_db)WIDTH;
	h->dirvector = player->dir;
	h->door_intersect.x = 0.0;
	h->door_intersect.y = 0.0;
	if (game->enemy_count > 0)
	{
		h->enemy_flags = (int *)malloc(sizeof(int) * game->enemy_count);
		err_check(h->enemy_flags, "malloc fucked the scene");
		i = 0;
		while (++i < game->enemy_count)
			h->enemy_flags[i] = 0;
	}
	else
		h->enemy_flags = NULL;
}

// looping through all screen x values and drwaing a vertical line
// of the door texture if there is one visible on screen.
void	draw_doors(t_game *game)
{
	t_doorhelp	h;

	get_screen(game, &game->player, &h);
	h.i = -1;
	while (++h.i < WIDTH && game->map.dstuff.nb > 0)
	{
		h.screen_x = point_x_vector(h.sl, (t_db)h.i, h.stepvector);
		check_intersect(game, &h, game->map.dstuff.doors, h.i);
		h.lineheight = (int)round((t_db)HEIGHT / h.dist);
		if (h.dist < (game->dist_arr[h.i]))
		{
			draw_doorline(game, &h, h.i);
			if (h.i == WIDTH / 2 && h.dist <= 2.0)
				game->map.dstuff.current = h.d;
			else if (h.i == WIDTH / 2)
				game->map.dstuff.current = NULL;
		}
		else if (h.i == WIDTH / 2)
			game->map.dstuff.current = NULL;
		h.y = -1;
		while (++h.y < game->enemy_count)
			h.enemy_flags[h.y] = 0;
	}
	if (h.enemy_flags)
		free(h.enemy_flags);
}
