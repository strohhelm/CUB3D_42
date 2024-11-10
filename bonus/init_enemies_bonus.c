/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_enemies.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: timschmi <timschmi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 11:53:58 by timschmi          #+#    #+#             */
/*   Updated: 2024/11/08 16:14:38 by timschmi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub_bonus.h"

void	append_node(t_ai **e, t_point pos, mlx_texture_t **idle,
		mlx_texture_t **dying)
{
	t_ai	*new_node;
	t_ai	*temp;

	new_node = NULL;
	temp = *e;
	new_node = (t_ai *)malloc(sizeof(t_ai));
	new_node->tex[0] = idle;
	new_node->tex[1] = dying;
	new_node->pos = pos;
	new_node->next = NULL;
	new_node->hp = 100;
	new_node->state = ALIVE;
	new_node->i = 0;
	new_node->hit = 0;
	if (!*e)
	{
		*e = new_node;
		return ;
	}
	while (temp->next)
		temp = temp->next;
	temp->next = new_node;
}

mlx_texture_t	**allocate_textures_idle(void)
{
	mlx_texture_t	**idle;

	idle = (mlx_texture_t **)malloc(sizeof(mlx_texture_t *) * 6);
	idle[0] = mlx_load_png("./include/textures/sprites/idle/tile000.png");
	idle[1] = mlx_load_png("./include/textures/sprites/idle/tile001.png");
	idle[2] = mlx_load_png("./include/textures/sprites/idle/tile002.png");
	idle[3] = mlx_load_png("./include/textures/sprites/idle/tile003.png");
	idle[4] = mlx_load_png("./include/textures/sprites/idle/tile004.png");
	idle[5] = mlx_load_png("./include/textures/sprites/idle/tile005.png");
	return (idle);
}

mlx_texture_t	**allocate_textures_dying(void)
{
	mlx_texture_t	**dying;

	dying = (mlx_texture_t **)malloc(sizeof(mlx_texture_t *) * 8);
	dying[0] = mlx_load_png("./include/textures/sprites/dying/dying1.png");
	dying[1] = mlx_load_png("./include/textures/sprites/dying/dying2.png");
	dying[2] = mlx_load_png("./include/textures/sprites/dying/dying3.png");
	dying[3] = mlx_load_png("./include/textures/sprites/dying/dying4.png");
	dying[4] = mlx_load_png("./include/textures/sprites/dying/dying5.png");
	dying[5] = mlx_load_png("./include/textures/sprites/dying/dying6.png");
	dying[6] = mlx_load_png("./include/textures/sprites/dying/dying7.png");
	dying[7] = mlx_load_png("./include/textures/sprites/dying/dying8.png");
	return (dying);
}

t_ai	*load_alien(t_game *game)
{
	int				count;
	t_point			pos;
	t_ai			*e;
	mlx_texture_t	**idle;
	mlx_texture_t	**dying;

	count = 3;
	e = NULL;
	pos.x = 4.5;
	pos.y = 1.5;
	idle = allocate_textures_idle(); // these two need to be freed somewhere!!!
	dying = allocate_textures_dying();
	while (count)
	{
		append_node(&e, pos, idle, dying);
		pos.x += 2.0;
		pos.y += 0.0;
		count--;
	}
	return (e);
}
