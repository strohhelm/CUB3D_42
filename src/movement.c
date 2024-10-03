/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pstrohal <pstrohal@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 14:52:15 by timschmi          #+#    #+#             */
/*   Updated: 2024/10/03 19:39:01 by pstrohal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

void	rotation_extra_keys(t_game *game)
{
	rotate_dir_plane(&game->player.dir, &game->player.scr, (game->x) * 0.0005,
		1);
	if (mlx_is_key_down(game->mlx, MLX_KEY_LEFT))
		rotate_dir_plane(&game->player.dir, &game->player.scr, 0.05, -1);
	if (mlx_is_key_down(game->mlx, MLX_KEY_RIGHT))
		rotate_dir_plane(&game->player.dir, &game->player.scr, 0.05, 1);
	if (mlx_is_key_down(game->mlx, MLX_KEY_ESCAPE))
	{
		mlx_terminate(game->mlx);
		mlx_set_cursor_mode(game->mlx, MLX_MOUSE_NORMAL);
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
		collision(*new_pos, game);
	}
	else if (key == 's')
	{
		new_pos->x = game->player.pos.x - game->player.dir.x * mod;
		new_pos->y = game->player.pos.y - game->player.dir.y * mod;
		collision(*new_pos, game);
	}
	else if (key == 'a')
	{
		new_pos->x = game->player.pos.x + game->player.dir.y * mod;
		new_pos->y = game->player.pos.y - game->player.dir.x * mod;
		collision(*new_pos, game);
	}
	else if (key == 'd')
	{
		new_pos->x = game->player.pos.x - game->player.dir.y * mod;
		new_pos->y = game->player.pos.y + game->player.dir.x * mod;
		collision(*new_pos, game);
	}
}

void	ft_hook(t_game *game)
{
	t_point	new_pos;
	int		mod;
	int		x;
	int		y;
	int		delta_y;

	mod = 0;
	x = 0;
	y = 0;
	delta_y = 0;
	mod = 1;
	mlx_get_mouse_pos(game->mlx, &x, &y);
	game->x = x - WIDTH / 2;
	if (mlx_is_key_down(game->mlx, MLX_KEY_LEFT_SHIFT))
		mod = 2;
	if (mlx_is_key_down(game->mlx, MLX_KEY_W))
		set_new_pos(game, &new_pos, 'w', mod);
	else if (mlx_is_key_down(game->mlx, MLX_KEY_S))
		set_new_pos(game, &new_pos, 's', mod);
	if (mlx_is_key_down(game->mlx, MLX_KEY_A))
		set_new_pos(game, &new_pos, 'a', mod);
	else if (mlx_is_key_down(game->mlx, MLX_KEY_D))
		set_new_pos(game, &new_pos, 'd', mod);
	rotation_extra_keys(game);
	mlx_set_mouse_pos(game->mlx, WIDTH / 2, HEIGHT / 2);
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
