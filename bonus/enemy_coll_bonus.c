/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy_coll_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pstrohal <pstrohal@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 13:16:49 by timschmi          #+#    #+#             */
/*   Updated: 2024/11/10 15:59:33 by pstrohal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub_bonus.h"

void	set_e_index(t_point new_pos, t_ai *e, int *ix, int *iy)
{
	double	radius;

	radius = 0.5;
	*ix = new_pos.x;
	*iy = new_pos.y;
	if ((new_pos.x - e->pos.x) < 0)
		*ix = new_pos.x - radius;
	else if ((new_pos.x - e->pos.x) > 0)
		*ix = new_pos.x + radius;
	if ((new_pos.y - e->pos.y) < 0)
		*iy = new_pos.y - radius;
	else if ((new_pos.y - e->pos.y) > 0)
		*iy = new_pos.y + radius;
}

void	e_collision(t_point new_pos, t_game *game, t_ai *e)
{
	int	ix;
	int	iy;

	set_e_index(new_pos, e, &ix, &iy);
	if (iy <= game->map.map_h && ix <= game->map.map_w
		&& game->map.map[iy][ix] == 0 && (game->map.map[iy][(int)e->pos.x] != 1
			&& game->map.map[(int)e->pos.y][ix] != 1))
	{
		if (!intersection_with_door(game, e->pos, new_pos))
			e->pos = new_pos;
	}
	else if (iy <= game->map.map_h && game->map.map[iy][(int)e->pos.x] != 1)
	{
		new_pos.x = e->pos.x;
		if (!intersection_with_door(game, e->pos, new_pos))
			e->pos = new_pos;
	}
	else if (ix <= game->map.map_w && game->map.map[(int)e->pos.y][ix] != 1)
	{
		new_pos.y = e->pos.y;
		if (!intersection_with_door(game, e->pos, new_pos))
			e->pos = new_pos;
	}
}

void	update_enemy_pos(t_ai **enemy, t_game *game)
{
	t_ai	*e;
	double	dist;
	t_point	move;
	double	len;

	e = *enemy;
	while (e)
	{
		if (e->state == DYING || e->state == DEAD)
		{
			e = e->next;
			continue ;
		}
		dist = sqrt(pow(game->player.pos.x - e->pos.x, 2.0)
				+ pow(game->player.pos.y - e->pos.y, 2.0));
		len = 0.03 / dist;
		move.x = e->pos.x + len * (game->player.pos.x - e->pos.x);
		move.y = e->pos.y + len * (game->player.pos.y - e->pos.y);
		e_collision(move, game, e);
		e = e->next;
	}
}
