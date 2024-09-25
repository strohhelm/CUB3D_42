/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pstrohal <pstrohal@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 14:52:15 by timschmi          #+#    #+#             */
/*   Updated: 2024/09/25 16:43:18 by pstrohal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

void	rotation_extra_keys(t_game *game)
{
	if (mlx_is_key_down(game->mlx, MLX_KEY_Q) || mlx_is_key_down(game->mlx, MLX_KEY_LEFT))
		rotate_dir_plane(&game->player.dir, &game->player.scr, 0.1, -1);
	if (mlx_is_key_down(game->mlx, MLX_KEY_E)|| mlx_is_key_down(game->mlx, MLX_KEY_RIGHT))
		rotate_dir_plane(&game->player.dir, &game->player.scr, 0.1, 1);
	if (mlx_is_key_down(game->mlx, MLX_KEY_ESCAPE))
	{
		mlx_terminate(game->mlx);
		exit(0);
	}
}

void	update_pos(t_game *game, t_point new_pos)
{
	game->player.pos.x = new_pos.x;
	game->player.pos.y = new_pos.y;
}

void	set_new_pos(t_game *game, t_point *new_pos, char key, int mod)
{
	if (key == 'w')
	{
		new_pos->x = game->player.pos.x + game->player.dir.x * mod;
		new_pos->y = game->player.pos.y + game->player.dir.y * mod;
	}
	else if (key == 's')
	{
		new_pos->x = game->player.pos.x - game->player.dir.x * mod;
		new_pos->y = game->player.pos.y - game->player.dir.y * mod;
	}
	else if (key == 'a')
	{
		new_pos->x = game->player.pos.x + game->player.dir.y * mod;
		new_pos->y = game->player.pos.y - game->player.dir.x * mod;
	}
	else if (key == 'd')
	{
		new_pos->x = game->player.pos.x - game->player.dir.y * mod;
		new_pos->y = game->player.pos.y + game->player.dir.x * mod;
	}
}

void	ft_hook(t_game *game)
{
	t_point	new_pos;
	int mod;
	
	mod = 1;
	if (mlx_is_key_down(game->mlx, MLX_KEY_LEFT_SHIFT))
		mod = 2;
	if (mlx_is_key_down(game->mlx, MLX_KEY_W))
	{
		set_new_pos(game, &new_pos, 'w', mod);
		collision(new_pos, game);
	}
	else if (mlx_is_key_down(game->mlx, MLX_KEY_S))
	{
		set_new_pos(game, &new_pos, 's', mod);
		collision(new_pos, game);
	}
	if (mlx_is_key_down(game->mlx, MLX_KEY_A))
	{
		set_new_pos(game, &new_pos, 'a', mod);
		collision(new_pos, game);
	}
	else if (mlx_is_key_down(game->mlx, MLX_KEY_D))
	{
		set_new_pos(game, &new_pos, 'd', mod);
		collision(new_pos, game);
	}
	rotation_extra_keys(game);
}

// speed = how much rotation per call of function,
//	l_r = left or right rotation; left -> l_r = 1, right -> l_r = -1;
void	rotate_dir_plane(t_point *dir, t_point *plane, double speed, double l_r)
{
	double	tmp_x;

	speed *= l_r;
	tmp_x = dir->x;
	dir->x = dir->x * cos(speed) - dir->y * sin(speed);
	dir->y = tmp_x * sin(speed) + dir->y * cos(speed);
	tmp_x = plane->x;
	plane->x = plane->x * cos(speed) - plane->y * sin(speed);
	plane->y = tmp_x * sin(speed) + plane->y * cos(speed);
}
