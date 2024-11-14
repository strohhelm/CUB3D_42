/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_init_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: timschmi <timschmi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 12:38:41 by timschmi          #+#    #+#             */
/*   Updated: 2024/11/14 12:39:24 by timschmi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub_bonus.h"

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
	game->cmg = NULL;
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
	allocate_images(game);
	allocate_all_textures(game);
	mlx_image_to_window(game->mlx, game->img, 0, 0);
	mlx_image_to_window(game->mlx, game->minimap, MINIMAP_P, MINIMAP_P);
	mlx_image_to_window(game->mlx, game->hp, 0, 0);
	load_gun(game);
	put_crosshair(game);
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
