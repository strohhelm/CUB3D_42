/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: timschmi <timschmi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 13:36:56 by timschmi          #+#    #+#             */
/*   Updated: 2024/09/30 15:24:48 by timschmi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

void second_init(t_game *game)
{
	double scale;
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

void init_game(t_game *game)
{
	game->player.height = HEIGHT;
	game->player.width = WIDTH;
	game->player.color = 0x6cf542ff;
	game->player.pov = 0.5;
	game->map.str_map = NULL;
	game->map.textures[CEILING] = mlx_load_png("./include/textures/floor.png");
	game->map.textures[FLOOR] = mlx_load_png("./include/textures/clouds.png");
}
void	leaks()
{
	system("leaks cub3d");
}

int main(int argc, char **argv)
{
	t_game game;
	
	// atexit(leaks);
	if (!(argc == 2))
		return (printf("invalid input!\n"));
	init_game(&game);
	if (read_input(argv, &game.player, &game.map))
		return (printf("invalid input!\n"), 0);
	screen_init(&game.player);
	second_init(&game);
	mlx_image_to_window(game.mlx, game.img, 0, 0);
	mlx_loop_hook(game.mlx, render, (void*)&game);
	mlx_loop(game.mlx);
	mlx_terminate(game.mlx);
	return (0);
}
