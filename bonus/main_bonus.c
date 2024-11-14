/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pstrohal <pstrohal@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 13:36:56 by timschmi          #+#    #+#             */
/*   Updated: 2024/11/14 15:14:48 by pstrohal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub_bonus.h"

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
	minimap_init(&game);
	health_bar(&game);
	display_enemycount(&game);
	mlx_set_cursor_mode(game.mlx, MLX_MOUSE_HIDDEN);
	mlx_key_hook(game.mlx, mouse, (void *)&game);
	mlx_loop_hook(game.mlx, render, (void *)&game);
	mlx_loop(game.mlx);
	free_game_end(&game);
	return (0);
}

void	allocate_images(t_game *game)
{
	game->img = mlx_new_image(game->mlx, WIDTH, HEIGHT);
	err_check(&game->img, "fucking malloc");
	game->emg = mlx_new_image(game->mlx, WIDTH, HEIGHT);
	err_check(&game->emg, "fucking malloc");
	game->minimap = mlx_new_image(game->mlx, MINIMAP_H, MINIMAP_H);
	err_check(&game->minimap, "fucking malloc");
	game->hp = mlx_new_image(game->mlx, WIDTH, HEIGHT);
	err_check(&game->hp, "fucking malloc");
	game->cross = mlx_new_image(game->mlx, CROSSHAIR, CROSSHAIR);
	err_check(&game->cross, "fucking malloc");
	allocate_textures_idle(game->e_idle);
	allocate_textures_dying(game->e_dying);
	game->enemy_count = 0;
	game->e = load_alien(game);
	game->l_img = NULL;
	game->w_img = NULL;
}

void	allocate_all_textures(t_game *game)
{
	game->map.indiv = allocate_textures(&game->map);
	game->map.textures[FLOOR] = NULL;
	game->map.textures[CEILING] = NULL;
	game->map.textures[BULLET] = mlx_load_png("./include/textures/bullet.png");
	err_check(game->map.textures[BULLET], "Cannot load bullet texture");
}
