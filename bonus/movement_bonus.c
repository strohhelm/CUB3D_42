/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pstrohal <pstrohal@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 14:52:15 by timschmi          #+#    #+#             */
/*   Updated: 2024/11/14 17:15:32 by pstrohal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub_bonus.h"

void	mouse(mlx_key_data_t key, void *par)
{
	t_game		*game;
	static int	m = 1;

	game = (t_game *)par;
	if (key.key == MLX_KEY_TAB && key.action == MLX_PRESS)
	{
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
	if (key.key == MLX_KEY_SPACE && key.action == MLX_PRESS)
		door_move(game, game->map.dstuff.current);
}

void	rotation_extra_keys(t_game *game)
{
	rotate_dir_plane(&game->player.dir, &game->player.scr, (game->x) * 0.0005,
		1);
	if (mlx_is_key_down(game->mlx, MLX_KEY_ESCAPE))
	{
		free_game_end(game);
		exit(0);
	}
}

void	mouse_hook(t_game *game)
{
	int	x;
	int	y;
	int	delta_y;

	if (game->mouse > 0)
	{
		x = 0;
		y = 0;
		delta_y = 0;
		mlx_get_mouse_pos(game->mlx, &x, &y);
		game->x = x - WIDTH / 2;
		delta_y = y - HEIGHT / 2;
		game->y += delta_y;
		if (game->y >= HEIGHT)
			game->y = HEIGHT - 1;
		else if (game->y < -(HEIGHT))
			game->y = -(HEIGHT) + 1;
	}
	else
		game->x = 0;
}

void	ft_hook(t_game *game)
{
	t_point	new_pos;
	int		mod;

	mod = 1;
	mouse_hook(game);
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
	if (mlx_is_mouse_down(game->mlx, MLX_MOUSE_BUTTON_LEFT)
		&& !game->player.attack)
		game->player.attack = 1;
	rotation_extra_keys(game);
	if (game->mouse > 0)
		mlx_set_mouse_pos(game->mlx, WIDTH / 2, HEIGHT / 2);
}
