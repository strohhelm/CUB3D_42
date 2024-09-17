/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collision.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: timschmi <timschmi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 14:51:18 by timschmi          #+#    #+#             */
/*   Updated: 2024/09/17 14:39:37 by timschmi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int collision(t_player player, t_game *game, int mod)
{
	double x;
	double y;
	double px = player.pos.x;
	double py = player.pos.y;
	if (mod == 1)
	{
		x = px + 0.11;
		y = py;
	}
	else if (mod == 2)
	{
		x = px - 0.11;
		y = py;
	}
	else if (mod == 3)
	{
		x = px;
		y = py + 0.11;
	}
	else if (mod == 4)
	{
		x = px;
		y = py - 0.11;
	}
	int ix = x;
	int iy = y;
	printf("player: x: %f y: %f, index: x: %d y: %d\n", x, y, ix, iy);
	if (game->map.map[ix][iy] == 1)
		return(0);
	return (1);
}