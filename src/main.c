/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pstrohal <pstrohal@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 13:36:56 by timschmi          #+#    #+#             */
/*   Updated: 2024/10/01 21:05:34 by pstrohal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

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
	game->img = mlx_new_image(game->mlx, WIDTH, HEIGHT);
}

void	init_game(t_game *game)
{
	game->player.height = HEIGHT;
	game->player.width = WIDTH;
	game->player.color = 0x6cf542ff;
	game->player.pov = 0.66;//(double) HEIGHT / (double) WIDTH;
	printf("%f\n", game->player.pov);
	game->map.str_map = NULL;
	game->map.textures[FLOOR] = mlx_load_png("./include/textures/5.png");
	if (!game->map.textures[FLOOR])
		error_print("Cannot load floor texture");
	game->map.textures[CEILING] = mlx_load_png("./include/textures/clouds.png");
	if (!game->map.textures[CEILING])
		error_print("Cannot load ceiling texture");
}

void	leaks(void)
{
	system("leaks cub3d");
}

int	main(int argc, char **argv)
{
	t_game	game;

	game_pointer(1, &game);
	if (!(argc == 2))
		return (printf("Wrong amount of arguments! need: 1\n"), 1);
	init_game(&game);
	read_input(argv, &game.player, &game.map);
	screen_init(&game.player);
	second_init(&game);
	mlx_image_to_window(game.mlx, game.img, 0, 0);
	mlx_loop_hook(game.mlx, render, (void *)&game);
	mlx_loop(game.mlx);
	mlx_terminate(game.mlx);
	return (0);
}
