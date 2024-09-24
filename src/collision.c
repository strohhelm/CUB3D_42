/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collision.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: timschmi <timschmi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 14:51:18 by timschmi          #+#    #+#             */
/*   Updated: 2024/09/24 15:26:52 by timschmi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

int	collision(t_point new_pos, t_game *game)
{
	int	ix;
	int	iy;

	// new_pos.x *= 1.2;
	// new_pos.y *= 1.2;
	ix = new_pos.x;
	iy = new_pos.y;
	if (iy <= game->map.map_w && ix <= game->map.map_h
		&& game->map.map[iy][ix] == 1)
		return (0);
	else
		update_pos(game, new_pos);
	return (1);
}
