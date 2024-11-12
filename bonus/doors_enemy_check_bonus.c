/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doors_enemy_check_bonus.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pstrohal <pstrohal@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 15:08:38 by pstrohal          #+#    #+#             */
/*   Updated: 2024/11/12 15:40:41 by pstrohal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub_bonus.h"

void	check_enemy_dist(t_game *game, t_doorhelp *h, uint id)
{
	t_ai	*enemy;

	enemy = game->e;
	while (enemy)
	{
		if (enemy->id == (int)id )
		{
			if (intersection_with_door(game, game->player.pos, enemy->pos))
				h->enemy_flags[id - 1] = -1;
			else
				h->enemy_flags[id - 1] = 1;
			return ;
		}
		enemy = enemy->next;
	}
}

void	check_emg(t_game *game, t_doorhelp *h)
{
	uint32_t	id;

	if (h->enemy_flags)
		id = *((uint32_t *)&game->emg[h->img_index]);
	else
		id = 0;
	if (id)
	{
		if (h->enemy_flags[id - 1] > 0)
			h->test = 0;
		else if (h->enemy_flags[id - 1] < 0)
			h->test = *((uint32_t *)h->tex_pos);
		else if (h->enemy_flags[id - 1] == 0)
			check_enemy_dist(game, h, id);
	}
	else
		h->test = *((uint32_t *)h->tex_pos);
	return ;
}