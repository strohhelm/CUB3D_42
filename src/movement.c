/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: timschmi <timschmi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 14:52:15 by timschmi          #+#    #+#             */
/*   Updated: 2024/09/19 15:09:19 by timschmi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

void ft_hook(mlx_key_data_t keydata, void *param)
{
	t_game *game;

	game = (t_game*)param;

	t_point new_pos;
	double dirx , diry;
	dirx = game->player.dir.x / 5 + game->player.pos.x;
	diry = game->player.dir.y / 5 + game->player.pos.y;

	if (keydata.key == MLX_KEY_W && (keydata.action == MLX_REPEAT || keydata.action == MLX_PRESS))
	{
		new_pos.x = dirx;
		new_pos.y = diry;
		if (collision(new_pos, game))
		{
			game->player.pos.x = new_pos.x;
			game->player.pos.y = new_pos.y;
		}
	}
	else if (keydata.key == MLX_KEY_S && (keydata.action == MLX_REPEAT || keydata.action == MLX_PRESS))
	{
		new_pos.x = game->player.pos.x - game->player.dir.x / 5;
		new_pos.y= game->player.pos.y - game->player.dir.y / 5;
		if (collision(new_pos, game))
		{
			game->player.pos.x = new_pos.x;
			game->player.pos.y = new_pos.y;
		}
	}
	else if (keydata.key == MLX_KEY_A && (keydata.action == MLX_REPEAT || keydata.action == MLX_PRESS))
	{
		dirx = game->player.dir.y;
		diry = (game->player.dir.x * -1);

		new_pos.x = game->player.pos.x + dirx * 0.2;
		new_pos.y = game->player.pos.y + diry * 0.2;
		if (collision(new_pos, game))
		{
			game->player.pos.x = new_pos.x;
			game->player.pos.y = new_pos.y;
		}

	}
	else if (keydata.key == MLX_KEY_D && (keydata.action == MLX_REPEAT || keydata.action == MLX_PRESS))
	{
		dirx = (game->player.dir.y * -1);
		diry = game->player.dir.x;

 		new_pos.x = game->player.pos.x + dirx * 0.2;
		new_pos.y = game->player.pos.y + diry * 0.2;
		if (collision(new_pos, game))
		{
			game->player.pos.x = new_pos.x;
			game->player.pos.y = new_pos.y;
		}

	}
	if (keydata.key == MLX_KEY_Q && (keydata.action == MLX_REPEAT || keydata.action == MLX_PRESS))
		{
			rotate_dir_plane(&game->player.dir, &game->player.scr, 0.1, -1);
			return ;
		}
	if (keydata.key == MLX_KEY_E && (keydata.action == MLX_REPEAT || keydata.action == MLX_PRESS))
		rotate_dir_plane(&game->player.dir, &game->player.scr, 0.1, 1);
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
