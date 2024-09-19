/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collision.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: timschmi <timschmi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 14:51:18 by timschmi          #+#    #+#             */
/*   Updated: 2024/09/19 15:10:56 by timschmi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

int collision(t_point new_pos, t_game *game)
{
	new_pos.x += 0.01;
	new_pos.y += 0.01;

	int ix = new_pos.x;
	int iy = new_pos.y;
	
	if (game->map.map[ix][iy] == 1)
		return(0);
	return (1);
}