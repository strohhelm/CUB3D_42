/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doors_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pstrohal <pstrohal@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 17:21:53 by pstrohal          #+#    #+#             */
/*   Updated: 2024/11/07 20:56:25 by pstrohal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../cub_bonus.h"

void get_screen(t_player *player, t_doorhelp *hlp)
{
	hlp->sl.x = player->pos.x - player->scr.x + player->dir.x;
	hlp->sl.y = player->pos.y - player->scr.y + player->dir.y;
	hlp->sr.x = player->pos.x + player->scr.x + player->dir.x;
	hlp->sr.y = player->pos.y + player->scr.y + player->dir.y;
	hlp->pos = player->pos;
	hlp->screenvector = vector(hlp->sl, hlp->sr);
	hlp->stepvector.x = hlp->screenvector.x / (double)WIDTH;
	hlp->stepvector.y = hlp->screenvector.y / (double)WIDTH;
	hlp->dirvector = player->dir;
}

void	draw_doorline(t_game *game, t_doorhelp *hlp, int x)
{
	int		i;
	
	i = 0;
	hlp->doorwidth = dist_points(hlp->d->p1, hlp->d->p2);
	hlp->start = -hlp->lineheight / 2 + HEIGHT / 2 - game->y;
	hlp->end = hlp->lineheight / 2 + HEIGHT / 2;
	hlp->tex_step = 1.0 * hlp->d->texture->height / hlp->lineheight;
	hlp->door_x = dist_points(hlp->d->p1, hlp->door_intersect);
	hlp->tex_coords.x = (double)hlp->d->texture->width
					/ (hlp->doorwidth / hlp->door_x);
	hlp->tex_coords.y = 0;
	while (i <= hlp->lineheight)
	{
		if (hlp->start + i >= 0 && hlp->start + i <= HEIGHT)
		{
			uint32_t tex_index = (((int)round(hlp->tex_coords.y)
					* hlp->d->texture->width) + (int)round(hlp->tex_coords.x) ) * 4;
			hlp->tex_pos = &hlp->d->texture->pixels[tex_index];
			hlp->img_pos = &game->img->pixels[(((hlp->start + i)
					* game->img->width) + x) * 4];
			ft_memmove(&hlp->test, hlp->tex_pos, 4);
			if (hlp->test)
				ft_memmove(hlp->img_pos, hlp->tex_pos, 4);
		}
		hlp->tex_coords.y += hlp->tex_step;
		i++;
	}
}

void	check_intersect(t_doorhelp *hlp, t_doorstuff *dstuff)
{
	t_door	*d;
	t_point	tmp;
	t_list	*doors;
	int		i;
	
	doors = dstuff->doors;
	hlp->dist = hlp->buffdist + 2.0;
	i = -1;
	while (doors)
	{
		d = (t_door *)doors->content;
		tmp = intersection(hlp->pos, hlp->screen_x, d->p1, d->p2);
		if (tmp.x && tmp.y)
		{
			hlp->tmpdist = dist_points(hlp->pos, tmp);
			hlp->angle = vector_angle(hlp->dirvector, vector(hlp->pos, hlp->screen_x));
			if (hlp->angle != 0.0)
				hlp->tmpdist *= cos(hlp->angle);
			if (hlp->tmpdist < hlp->buffdist)
			{
				hlp->dist = hlp->tmpdist;
				hlp->door_intersect = tmp;
				hlp->d = d;
			}
		}
		doors = doors->next;
	}
}

void	draw_doors(t_game *game)
{
	t_doorhelp	hlp;
	int i;

	get_screen(&game->player, &hlp);
	i = - 1;
	hlp.door_intersect.x = 0.0;
	hlp.door_intersect.y = 0.0;
	while (++i < WIDTH && game->map.dstuff.nb > 0)
	{
		hlp.screen_x = point_x_vector(hlp.sl, (double)i, hlp.stepvector);
		hlp.buffdist = game->map.dist_buffer[i];
		check_intersect(&hlp, &game->map.dstuff);
		hlp.lineheight = (int)round((double)HEIGHT / hlp.dist);
		if (hlp.dist < (game->map.dist_buffer[i]))
		{
			draw_doorline(game, &hlp, i);
			if (i == WIDTH / 2)
				game->map.dstuff.current = hlp.d;
		}
		else if (i == WIDTH / 2)
			game->map.dstuff.current = NULL;
	}
}
