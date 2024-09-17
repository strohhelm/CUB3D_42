/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: timschmi <timschmi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 14:52:15 by timschmi          #+#    #+#             */
/*   Updated: 2024/09/17 14:25:00 by timschmi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void ft_hook(mlx_key_data_t keydata, void *param)
{
	t_game *game;

	game = (t_game*)param;

	if (keydata.key == MLX_KEY_W && (keydata.action == MLX_REPEAT || keydata.action == MLX_PRESS))
	{
		if (collision(game->player, game, 4))
			game->player.pos.y -= 0.1;
	}
	if (keydata.key == MLX_KEY_S && (keydata.action == MLX_REPEAT || keydata.action == MLX_PRESS))
	{
		if (collision(game->player, game, 3))
			game->player.pos.y += 0.1;
	}
	if (keydata.key == MLX_KEY_D && (keydata.action == MLX_REPEAT || keydata.action == MLX_PRESS))
	{
		if (collision(game->player, game, 1))
			game->player.pos.x += 0.1;
	}
	if (keydata.key == MLX_KEY_A && (keydata.action == MLX_REPEAT || keydata.action == MLX_PRESS))
	{
		if (collision(game->player, game, 2))
			game->player.pos.x -= 0.1;
	}
	if (keydata.key == MLX_KEY_Q && (keydata.action == MLX_REPEAT || keydata.action == MLX_PRESS))
		rotate_dir_plane(&game->player.dir, &game->player.scr, 0.1, -1);
	if (keydata.key == MLX_KEY_E && (keydata.action == MLX_REPEAT || keydata.action == MLX_PRESS))
		rotate_dir_plane(&game->player.dir, &game->player.scr, 0.1, 1);

	printf("px: %f, py: %f\n", game->player.pos.x, game->player.pos.y);
}

//speed = how much rotation per call of function, l_r = left or right rotation; left -> l_r = 1, right -> l_r = -1;
void rotate_dir_plane(t_point *dir, t_point *plane, double speed, double l_r)
{
	double tmp_x;

	speed *= l_r;
	tmp_x = dir->x;
	dir->x = dir->x * cos(speed) - dir->y * sin(speed);
	dir->y = tmp_x * sin(speed) + dir->y * cos(speed);
	tmp_x = plane->x;
	plane->x = plane->x * cos(speed) - plane->y * sin(speed);
	plane->y = tmp_x * sin(speed) + plane->y * cos(speed);
}
