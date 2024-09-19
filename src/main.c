/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pstrohal <pstrohal@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 13:36:56 by timschmi          #+#    #+#             */
/*   Updated: 2024/09/18 18:18:55 by pstrohal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

void grid(t_game *game)
{
	int x = 0;
	int y = 0;
	int fy;
	int fx;

	while (y < HEIGHT)
	{
		fy = (int)y / game->map.scale;
		x = 0;
		while (x < WIDTH / 2)
		{
			fx = (int)x / game->map.scale;
			if (fx < game->map.map_w && fy < game->map.map_h)
			{
				if (game->map.map[fy][fx] == 1)
					mlx_put_pixel(game->img, x, y, 0xD3D3D3FF);
				else if (game->map.map[fy][fx] == 0)
					mlx_put_pixel(game->img, x, y, 0x808080FF);
				else if (game->map.map[fy][fx] == -1)
					mlx_put_pixel(game->img, x, y, 0x000000FF);
			}
			x++;
		}
		y++;
	}
}

void draw_player(t_game *game)
{
	int scale = game->map.scale;
	int posx = game->player.pos.x * scale - 5;
	int posy = game->player.pos.y * scale - 5;
	int x = 0;
	int y = 0;

	while (y < 10)
	{
		x = 0;
		posx = game->player.pos.x * scale - 5;
		while (x < 10)
		{
			mlx_put_pixel(game->img, posx, posy, 0xFFFF00FF);
			x++;
			posx++;
		}
		y++;
		posy++;
	}
}

void player_dir_line(t_game *game)
{
	t_point player;
	t_point dir;
	t_point scr_start;
	t_point scr_end;
	
	player.x = game->player.pos.x * game->map.scale;
	player.y = game->player.pos.y * game->map.scale;
	mlx_put_pixel(game->img, player.x, player.y, 0x0F00FFF);
	// printf("player: %f %f\n", player.x, player.y);
	dir.x = (game->player.pos.x + game->player.dir.x) * game->map.scale;
	dir.y = (game->player.pos.y + game->player.dir.y )* game->map.scale;
	// printf("dir: %f %f\n", dir.x, dir.y);
	draw_line(&player, &dir, game, 0xFF00FFF);
	
	scr_start.x = (game->player.pos.x + game->player.dir.x - game->player.scr.x) * game->map.scale;
	scr_start.y = (game->player.pos.y + game->player.dir.y - game->player.scr.y) * game->map.scale;
	mlx_put_pixel(game->img, scr_start.x, scr_start.y, 0xFFFF00F);
	scr_end.x = (game->player.pos.x + game->player.dir.x + game->player.scr.x) * game->map.scale;
	scr_end.y = (game->player.pos.y + game->player.dir.y + game->player.scr.y) * game->map.scale;
	draw_line(&scr_start, &scr_end, game, 0x00FF00FF);
}

void blank(t_game *game)
{
	int x = WIDTH/2;
	int y = 0;

	while (x < WIDTH)
	{
		y = 0;
		while (y <= (HEIGHT / 2))
			mlx_put_pixel(game->img, x, y++, game->map.ceiling);
		while (y < (HEIGHT))
			mlx_put_pixel(game->img, x, y++, game->map.floor);
		x++;
	}
}



void	screen_init(t_player *player)
{
	t_point dir;
	t_point scr;

	dir = player->dir;
	scr.x = 0;
	scr.y = 0;
	if (dir.y > 0)
		scr.x = -player->pov;
	else if (dir.y < 0)
		scr.x = player->pov;
	else if (dir.x > 0)
		scr.y = player->pov;
	else if (dir.x < 0)
		scr.y = -player->pov;
	// printf("dir: %f %f\n", dir.x, dir.y);
	// printf("scr: %f %f\n", scr.x, scr.y);
	player->scr = scr;
}

void render(void *param)
{
	t_game *game;

	game = (t_game*)param;
	grid(game);
	blank(game);
	raycasting(game);
	draw_player(game);
	player_dir_line(game);
	mlx_image_to_window(game->mlx, game->img, 0, 0);
	usleep(1000);
}
void	load_textures(t_map *map)
{
	map->north = mlx_load_png("./include/textures/3.png");
}

int main(int argc, char **argv)
{
	t_game game;
	
	int scale;
	if (!(argc == 2))
		return (printf("invalid input!\n"));
	game.player.height = HEIGHT;
	game.player.width = WIDTH;
	game.player.color = 0x6cf542ff;
	game.player.pov = 0.5;
	game.map.str_map = NULL;
	game.map.ceiling = 0x00d4ffff;
	game.map.floor = 0x119c02ff; 
	if (read_input(argv, &game.player, &game.map))
		return (printf("invalid input!\n"), 0);
	screen_init(&game.player);
	load_textures(&game.map);
	if ((HEIGHT / game.map.map_h) < (WIDTH/2 / game.map.map_w))
		scale = (HEIGHT / game.map.map_h);
	else
		scale = ((WIDTH/2 / game.map.map_w));
		game.map.scale = scale;
	game.player.pos.x = (game.player.pos.x * scale + scale / 2) / scale;
	game.player.pos.y = (game.player.pos.y * scale + scale / 2) / scale;
	game.mlx = mlx_init(WIDTH, HEIGHT, "cub3d", true);
	game.img = mlx_new_image(game.mlx, WIDTH, HEIGHT);
	// for (uint32_t i = 0; i < game.map.north->height; i++ && i < HEIGHT)
	// {
	// 	for(u_int32_t j = 0; j < game.map.north->width; j++ && j < WIDTH)
	// 	{
	// 		uint8_t *pos = &game.map.north->pixels[(i * game.map.north->width + j) * game.map.north->bytes_per_pixel];
			
	// 		uint8_t *img_pos = &game.img->pixels[(i * game.img->width + j) * game.map.north->bytes_per_pixel];
	// 		memmove(img_pos, pos , game.map.north->bytes_per_pixel);
	// 	}
	// }
	mlx_image_to_window(game.mlx, game.img, 0, 0);
	mlx_key_hook(game.mlx, &ft_hook, (void*)&game);
	mlx_loop_hook(game.mlx, render, (void*)&game);
	mlx_loop(game.mlx);
	mlx_terminate(game.mlx);
	return (0);
}
