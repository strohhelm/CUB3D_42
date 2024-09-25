/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collision.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pstrohal <pstrohal@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 14:51:18 by timschmi          #+#    #+#             */
/*   Updated: 2024/09/25 16:16:05 by pstrohal         ###   ########.fr       */
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
	if (iy <= game->map.map_h && ix <= game->map.map_w
		&& game->map.map[iy][ix] == 0)
		update_pos(game, new_pos);
	else
		return (0);
	return (1);
}
