/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pstrohal <pstrohal@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 14:52:15 by timschmi          #+#    #+#             */
/*   Updated: 2024/09/23 18:16:08 by pstrohal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

void ft_hook(t_game *game)
{
	// t_game *game;

	// game = (t_game*)param;

	t_point new_pos;
	double dirx , diry;
	dirx = game->player.dir.x + game->player.pos.x;
	diry = game->player.dir.y + game->player.pos.y;

	if (mlx_is_key_down(game->mlx, MLX_KEY_W))
	{
		new_pos.x = dirx;
		new_pos.y = diry;
		if (collision(new_pos, game))
		{
			game->player.pos.x = new_pos.x;
			game->player.pos.y = new_pos.y;
		}
	}
	if (mlx_is_key_down(game->mlx, MLX_KEY_S))
	{
		new_pos.x = game->player.pos.x - game->player.dir.x ;
		new_pos.y= game->player.pos.y - game->player.dir.y;
		if (collision(new_pos, game))
		{
			game->player.pos.x = new_pos.x;
			game->player.pos.y = new_pos.y;
		}
	}
	if (mlx_is_key_down(game->mlx, MLX_KEY_A))
	{
		dirx = game->player.dir.y;
		diry = (game->player.dir.x * -1);

		new_pos.x = game->player.pos.x + dirx;
		new_pos.y = game->player.pos.y + diry;
		if (collision(new_pos, game))
		{
			game->player.pos.x = new_pos.x;
			game->player.pos.y = new_pos.y;
		}

	}
	if (mlx_is_key_down(game->mlx, MLX_KEY_D))
	{
		dirx = (game->player.dir.y * -1);
		diry = game->player.dir.x;

 		new_pos.x = game->player.pos.x + dirx;
		new_pos.y = game->player.pos.y + diry;
		if (collision(new_pos, game))
		{
			game->player.pos.x = new_pos.x;
			game->player.pos.y = new_pos.y;
		}

	}
	if (mlx_is_key_down(game->mlx, MLX_KEY_LEFT))
		{
			rotate_dir_plane(&game->player.dir, &game->player.scr, 0.1, -1);
			return ;
		}
	if (mlx_is_key_down(game->mlx, MLX_KEY_RIGHT))
		rotate_dir_plane(&game->player.dir, &game->player.scr, 0.1, 1);
	if (mlx_is_key_down(game->mlx, MLX_KEY_ESCAPE))
	{
		mlx_terminate(game->mlx);
		exit(0);
	}
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
