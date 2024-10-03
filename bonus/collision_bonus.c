/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collision_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pstrohal <pstrohal@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 14:51:18 by timschmi          #+#    #+#             */
/*   Updated: 2024/10/03 19:54:47 by pstrohal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub_bonus.h"

void	collision(t_point new_pos, t_game *game)
{
	int	ix;
	int	iy;

	ix = new_pos.x;
	iy = new_pos.y;
	if (iy <= game->map.map_h && ix <= game->map.map_w
		&& game->map.map[iy][ix] == 0)
	{
		if (game->map.map[iy][(int)game->player.pos.x] == 0
			&& game->map.map[(int)game->player.pos.y][ix] == 0)
			update_pos(game, new_pos);
	}
	else if (iy <= game->map.map_h
		&& game->map.map[iy][(int)game->player.pos.x] == 0)
	{
		new_pos.x = game->player.pos.x;
		update_pos(game, new_pos);
	}
	else if (ix <= game->map.map_w
		&& game->map.map[(int)game->player.pos.y][ix] == 0)
	{
		new_pos.y = game->player.pos.y;
		update_pos(game, new_pos);
	}
}
