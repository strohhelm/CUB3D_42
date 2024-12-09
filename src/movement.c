/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pstrohal <pstrohal@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 14:52:15 by timschmi          #+#    #+#             */
/*   Updated: 2024/11/27 14:35:47 by pstrohal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

void	mouse(mouse_key_t butt, action_t act, modifier_key_t mod, void *par)
{
	t_game		*game;
	static int	m = 1;

	if (butt == 0 && act == MLX_PRESS && !mod)
	{
		game = (t_game *)par;
		game->mouse *= -1;
		if (m != game->mouse && game->mouse > 0)
		{
			mlx_set_mouse_pos(game->mlx, WIDTH / 2, HEIGHT / 2);
			mlx_set_cursor_mode(game->mlx, MLX_MOUSE_HIDDEN);
			m = game->mouse;
		}
		else if (m != game->mouse && game->mouse < 0)
		{
			mlx_set_cursor_mode(game->mlx, MLX_MOUSE_NORMAL);
			m = game->mouse;
		}
	}
}

void	rotation_extra_keys(t_game *game)
{
	rotate_dir_plane(&game->player.dir, &game->player.scr, (game->x) * 0.0005,
		1);
	if (mlx_is_key_down(game->mlx, MLX_KEY_LEFT))
		rotate_dir_plane(&game->player.dir, &game->player.scr, 0.05, -1);
	if (mlx_is_key_down(game->mlx, MLX_KEY_RIGHT))
		rotate_dir_plane(&game->player.dir, &game->player.scr, 0.05, 1);
	if (mlx_is_key_down(game->mlx, MLX_KEY_ESCAPE))
		free_game_end(game);
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

	mod = 1;
	game->x = 0;
	if (game->mouse > 0)
	{
		mlx_get_mouse_pos(game->mlx, &x, &y);
		game->x = x - WIDTH / 2;
	}
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
	if (game->mouse > 0)
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
