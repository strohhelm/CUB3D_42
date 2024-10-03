/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: timschmi <timschmi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 13:36:56 by timschmi          #+#    #+#             */
/*   Updated: 2024/10/03 16:06:34 by timschmi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

int	main(int argc, char **argv)
{
	t_game	game;

	atexit(leaks);
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

void	init_game(t_game *game)
{
	game->x = 0;
	game->y = 0;
	game->player.height = HEIGHT;
	game->player.width = WIDTH;
	game->player.color = 0x6cf542ff;
	game->player.pov = 0.66;
	game->map.str_map = NULL;
	game->map.textures[FLOOR] = 
		mlx_load_png("./include/textures/minecraft_grass.png");
	if (!game->map.textures[FLOOR])
		error_print("Cannot load floor texture");
	game->map.textures[CEILING] = mlx_load_png("./include/textures/clouds.png");
	if (!game->map.textures[CEILING])
		error_print("Cannot load ceiling texture");
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
	game->img = mlx_new_image(game->mlx, WIDTH, HEIGHT);
}

void	leaks(void)
{
	system("leaks cub3d");
}
