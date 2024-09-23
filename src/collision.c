/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collision.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pstrohal <pstrohal@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 14:51:18 by timschmi          #+#    #+#             */
/*   Updated: 2024/09/20 20:19:42 by pstrohal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

int collision(t_point new_pos, t_game *game)
{
	// new_pos.x *= 1.2;
	// new_pos.y *= 1.2;

	int ix = new_pos.x;
	int iy = new_pos.y;
	
	if (iy <= game->map.map_w && ix <= game->map.map_h && game->map.map[iy][ix] == 1)
		return(0);
	return (1);
}