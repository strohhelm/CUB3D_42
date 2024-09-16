/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: timschmi <timschmi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 13:36:56 by timschmi          #+#    #+#             */
/*   Updated: 2024/09/16 15:49:59 by timschmi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void grid(t_game *game)
{
	int x = 0;
	int y = 0;

	game->map.map = (int**)malloc(sizeof(int*) * 10);
	while (x < 10)
	{
		game->map.map[x] = (int*)malloc(sizeof(int) * 10);
		x++;
	}

	int arr[10][10] = {
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 1, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 1, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
	};

	x = 0;
	while (x < 10)
	{
		y = 0;
		while (y < 10)
		{
			game->map.map[x][y] = arr[x][y];
			y++;
		}
		x++;
	}

	x = 0;
	y = 0;

	while (x < 10)
	{
		y = 0;
		while (y < 10)
		{
			int arr_x = x * 80;
			int arr_y = y * 80;

			while (arr_x < (x * 80 + 80))
			{
				arr_y = y * 80;
				while (arr_y < (y * 80 + 80))
				{
					if ((arr_x == x * 80 || arr_y == y * 80) || (arr_x == 799 || arr_y == 799)) // if the current pixel is in the border of the block or the edges of our window its painted black to create a grid layout
						mlx_put_pixel(game->img, arr_x, arr_y, 0x000000FF);
					else if (game->map.map[x][y] == 1)
						mlx_put_pixel(game->img, arr_x, arr_y, 0xD3D3D3FF);
					else
						mlx_put_pixel(game->img, arr_x, arr_y, 0x808080FF);
					arr_y++;
				}
				arr_x++;
			}
			y++;
		}
		x++;
	}
}

void draw_player(mlx_image_t *img, t_player *player)
{
	int x = player->pos.x * 80 - 10;
	int y = player->pos.y * 80 - 10;
	int size_x = 0;
	int size_y = 0;

	// double scalex = double(WIDTH / 10);
	// double scaley = double(HEIGHT / 10);
	// printf("draw x: %d, y: %d\n", x, y);

	while (size_x < 20)
	{
		y = player->pos.y * 80 - 10;
		size_y = 0;
		while (size_y < 20)
		{
			mlx_put_pixel(img, x, y, 0xFFFF00FF);
			y++;
			size_y++;
		}
		x++;
		size_x++;
	}
}

void player_dir_line(t_game *game)
{
	t_point temp_dir;
	t_point temp_scr_start;
	t_point temp_scr_end;

	temp_dir.x = game->player.pos.x + game->player.dir.x;
	temp_dir.y = game->player.pos.y + game->player.dir.y;
	printf("point a(x: %f, y: %f) || point b(x: %f, y: %f)\n", game->player.pos.x, game->player.pos.y, temp_dir.x, temp_dir.y);
	draw_line(&game->player.pos, &temp_dir, game, 0xFFFF00FF);
	temp_scr_start.x = temp_dir.x - game->player.scr.x;
	temp_scr_start.y = temp_dir.y - game->player.scr.y;
	temp_scr_end.x = temp_dir.x + game->player.scr.x;
	temp_scr_end.y = temp_dir.y + game->player.scr.y;
	draw_line(&temp_scr_start, &temp_scr_end, game, 0x00FF00FF);
}

void render(void *param)
{
	t_game *game;

	game = (t_game*)param;
	grid(game);
	draw_player(game->img, &game->player);
	player_dir_line(game);
	raycasting(game);
	mlx_image_to_window(game->mlx, game->img, 0, 0);
	usleep(100000);
}

int main(void)
{
	t_game game;

	game.player.pos.x = 1.5;
	game.player.pos.y = 1.5;
	game.player.height = HEIGHT;
	game.player.width = WIDTH;
	game.player.color = 0x6cf542ff;
	game.player.dir.x = 0.5;
	game.player.dir.y = 0;
	game.player.scr.x = 0;
	game.player.scr.y = 0.5;

	game.mlx = mlx_init(WIDTH, HEIGHT, "cub3d", true);
	
	game.img = mlx_new_image(game.mlx, WIDTH, HEIGHT);

	mlx_key_hook(game.mlx, &ft_hook, (void*)&game);
	mlx_loop_hook(game.mlx, render, (void*)&game);
	mlx_loop(game.mlx);
	mlx_terminate(game.mlx);
	return (0);
}
