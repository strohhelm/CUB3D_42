/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pstrohal <pstrohal@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 13:36:56 by timschmi          #+#    #+#             */
/*   Updated: 2024/11/10 13:40:42 by pstrohal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub_bonus.h"

int	main(int argc, char **argv)
{
	t_game	game;

	// atexit((void *)leaks);
	game_pointer(1, &game);
	if (!(argc == 2))
		return (printf("Wrong amount of arguments! need: 1\n"), 1);
	init_game(&game);
	read_input(argv, &game.player, &game.map);
	screen_init(&game.player);
	second_init(&game);
	minimap_init(&game);
	mlx_image_to_window(game.mlx, game.img, 0, 0);
	mlx_image_to_window(game.mlx, game.minimap, MINIMAP_P, MINIMAP_P);
	put_crosshair(&game);
	load_gun(&game);
	mlx_set_cursor_mode(game.mlx, MLX_MOUSE_HIDDEN);
	mlx_key_hook(game.mlx, mouse, (void *)&game);
	mlx_loop_hook(game.mlx, render, (void *)&game);
	mlx_loop(game.mlx);
	free_game_end(&game);
	return (0);
}

void	init_game(t_game *game)
{
	game->x = 0;
	game->y = 0;
	game->mouse = 1;
	game->player.height = HEIGHT;
	game->player.width = WIDTH;
	game->player.color = 0x6cf542ff;
	game->player.pov = 0.66;
	game->over = 0;
	game->player.attack = 0;
	game->player.hp = 100;
	game->scale = 10;
	game->map.str_map = NULL;
	game->map.dstuff.nb = 0;
	game->map.dstuff.doors = NULL;
	game->map.dstuff.current = NULL;
	game->map.textures[FLOOR] = mlx_load_png("./include/textures/red.png");
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
	game->map.indiv = allocate_textures(game->map.map_h, game->map.map_w, game->map.textures, game->map.map);
	game->mlx = mlx_init(WIDTH, HEIGHT, "cub3d", true);
	game->img = mlx_new_image(game->mlx, WIDTH, HEIGHT);
	game->minimap = mlx_new_image(game->mlx, MINIMAP_H, MINIMAP_H);
}
void	screen_init(t_player *player)
{
	t_point	dir;
	t_point	scr;

	dir = player->dir;
	player->dir.x /= 10;
	player->dir.y /= 10;
	scr.x = 0;
	scr.y = 0;
	if (dir.y > 0)
		scr.x = (-player->pov) / 10;
	else if (dir.y < 0)
		scr.x = player->pov / 10;
	else if (dir.x > 0)
		scr.y = player->pov / 10;
	else if (dir.x < 0)
		scr.y = -player->pov / 10;
	player->scr = scr;
}

int	leaks(void)
{
	return (system("leaks cub3d"));
}
