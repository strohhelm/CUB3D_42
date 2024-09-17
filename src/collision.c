/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collision.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pstrohal <pstrohal@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 14:51:18 by timschmi          #+#    #+#             */
/*   Updated: 2024/09/16 19:16:29 by pstrohal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

int collision(t_player player, t_game *game, int mod)
{
	double x;
	double y;
	double px = player.pos.x;
	double py = player.pos.y;
	if (mod == 1)
	{
		x = px + 0.1;
		y = py;
	}
	else if (mod == 2)
	{
		x = px - 0.1;
		y = py;
	}
	else if (mod == 3)
	{
		x = px;
		y = py + 0.1;
	}
	else if (mod == 4)
	{
		x = px;
		y = py - 0.1;
	}
	int ix = x;
	int iy = y;
	printf("player: x: %f y: %f, index: x: %d y: %d\n", player.pos.x, player.pos.y, ix, iy);
	if (game->map.map[ix][iy] == 1)
		return(0);
	return (1);
}