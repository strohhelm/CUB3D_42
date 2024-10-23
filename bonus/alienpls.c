/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alienpls.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: timschmi <timschmi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 17:00:03 by timschmi          #+#    #+#             */
/*   Updated: 2024/10/23 19:09:38 by timschmi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub_bonus.h"

void append_node(t_ai **e, t_point pos)
{
	t_ai *new_node = NULL;
	t_ai *temp;
	temp = *e;

	new_node = (t_ai*)malloc(sizeof(new_node));

	new_node->tex = mlx_load_png("./include/textures/ALIEN.png");
	new_node->pos = pos;
	new_node->next = NULL;
	if (!*e)
	{
		*e = new_node; 
		return;
	}
	
	while (temp->next)
		temp = temp->next;
	temp->next = new_node;
}

void load_alien(t_game *game)
{
	int count = 3;
	t_point pos;
	t_ai *e = NULL;


	while(count)
	{
		append_node(&e, pos);
		count--;
	}
	while(e)
	{
		printf("haha\n");
		e = e->next;
	}

	// e.tex = mlx_load_png("./include/textures/ALIEN.png");
	// mlx_image_t *alien = mlx_texture_to_image(game->mlx, e.tex);
	// mlx_image_to_window(game->mlx, alien, 0, 0);
}

void enemy_dist(t_game *game, t_ai *enemy)
{
	t_ai e;

	t_point p = game->player.pos;

	double len1;
	double len2;

	e.pos.x = 12.5;
	e.pos.y = 1.5;

	len1 = fabs(e.pos.x - p.x);
	len2 = fabs(e.pos.y - p.y);
	
	e.dist = sqrt(pow(len1, 2.0) + pow(len2, 2.0));

	printf("Player: x:%lf, y:%lf\nDist: %lf\n", p.x, p.y, e.dist);
}
