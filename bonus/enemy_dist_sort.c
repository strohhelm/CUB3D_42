/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy_dist_sort.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: timschmi <timschmi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 16:15:03 by timschmi          #+#    #+#             */
/*   Updated: 2024/11/08 16:15:49 by timschmi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub_bonus.h"

void	swap(t_ai **head)
{
	t_ai	*first;
	t_ai	*second;

	first = *head;
	second = (*head)->next;
	first->next = second->next;
	second->next = first;
	*head = second;
}

void sort_ai(t_ai **enemy)
{
	t_ai **temp = enemy;

	while((*temp)->next)
	{
		if ((*temp)->next->dist > (*temp)->dist)
		{
			swap(temp);
			temp = enemy;
		}
		else
			temp = &(*temp)->next;
	}
}

void enemy_dist(t_game *game, t_ai **enemy, int frame)
{
	t_ai *e;
	t_point p;
	t_point len;

	e = *enemy;
	p = game->player.pos;
	while(e)
	{
		len.x = fabs(e->pos.x - p.x);
		len.y = fabs(e->pos.y - p.y);
		
		e->dist = sqrt(pow(len.x, 2.0) + pow(len.y, 2.0));
		if (e->state == ALIVE && e->dist <= 0.5 && game->player.hp > 0)
		{
			game->player.hp -= 5;
			health_bar(game);
			game_over_check(game);
		}
		e = e->next;
	}
	sort_ai(enemy);
	draw_sprites(game, *enemy, frame);
}
