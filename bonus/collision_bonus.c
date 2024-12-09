/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collision_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: timschmi <timschmi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 14:51:18 by timschmi          #+#    #+#             */
/*   Updated: 2024/11/11 16:29:23 by timschmi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub_bonus.h"

void	set_index(t_point new_pos, t_game *game, int *ix, int *iy)
{
	double	radius;

	radius = 0.15;
	*ix = new_pos.x;
	*iy = new_pos.y;
	if ((new_pos.x - game->player.pos.x) < 0)
		*ix = new_pos.x - radius;
	else if ((new_pos.x - game->player.pos.x) > 0)
		*ix = new_pos.x + radius;
	if ((new_pos.y - game->player.pos.y) < 0)
		*iy = new_pos.y - radius;
	else if ((new_pos.y - game->player.pos.y) > 0)
		*iy = new_pos.y + radius;
}

void	collision(t_point new_pos, t_game *game)
{
	int	ix;
	int	iy;

	set_index(new_pos, game, &ix, &iy);
	if (iy <= game->map.map_h && ix <= game->map.map_w
		&& game->map.map[iy][ix] != 1
		&& (game->map.map[iy][(int)game->player.pos.x] != 1
			&& game->map.map[(int)game->player.pos.y][ix] != 1))
	{
		update_pos(game, new_pos);
	}
	else if (iy <= game->map.map_h
		&& game->map.map[iy][(int)game->player.pos.x] != 1)
	{
		new_pos.x = game->player.pos.x;
		update_pos(game, new_pos);
	}
	else if (ix <= game->map.map_w
		&& game->map.map[(int)game->player.pos.y][ix] != 1)
	{
		new_pos.y = game->player.pos.y;
		update_pos(game, new_pos);
	}
}
