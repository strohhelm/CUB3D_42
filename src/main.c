/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: timschmi <timschmi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 13:36:56 by timschmi          #+#    #+#             */
/*   Updated: 2024/11/13 17:32:53 by timschmi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

// atexit((void *)leaks);

// int	leaks(void)
// {
// 	return (system("leaks cub3d"));
// }

int	main(int argc, char **argv)
{
	t_game	game;

	if (!(argc == 2))
		return (printf("Wrong amount of arguments! need: 1\n"), 1);
	game_pointer(1, &game);
	init_game(&game);
	read_input(argv, &game.player, &game.map);
	screen_init(&game.player);
	second_init(&game);
	mlx_loop_hook(game.mlx, render, (void *)&game);
	mlx_mouse_hook(game.mlx, mouse, (void *)&game);
	mlx_set_cursor_mode(game.mlx, MLX_MOUSE_HIDDEN);
	mlx_loop(game.mlx);
	free_game_end(&game);
	exit (0);
}

void	init_game(t_game *game)
{
	game->x = 0;
	game->y = 0;
	game->mouse = -1;
	game->player.pov = 0.66;
	game->map.str_map = NULL;
}

void	second_init(t_game *game)
{
	double	scale;

	if ((HEIGHT / game->map.map_h) < (WIDTH / game->map.map_w))
		scale = (HEIGHT / game->map.map_h);
	else
		scale = (WIDTH / game->map.map_w);
	game->map.scale = scale;
	game->player.pos.x += 0.5;
	game->player.pos.y += 0.5;
	game->mlx = mlx_init(WIDTH, HEIGHT, "cub3d", true);
	mlx_set_window_limit(game->mlx, WIDTH, HEIGHT, WIDTH, HEIGHT);
	game->img = mlx_new_image(game->mlx, WIDTH, HEIGHT);
	mlx_image_to_window(game->mlx, game->img, 0, 0);
}
