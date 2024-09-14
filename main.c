/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: timschmi <timschmi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 13:36:56 by timschmi          #+#    #+#             */
/*   Updated: 2024/09/14 18:34:55 by timschmi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void grid(t_game *game)
{
	int x = 0;
	int y = 0;

	game->map = (int**)malloc(sizeof(int*) * 10);
	while (x < 10)
	{
		game->map[x] = (int*)malloc(sizeof(int) * 10);
		x++;
	}

	int arr[10][10] = {
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
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
			game->map[x][y] = arr[x][y];
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
					else if (game->map[x][y] == 1)
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
	int x = (int)player->pos.x - 10;
	int y = (int)player->pos.y - 10;
	int size_x = 0;
	int size_y = 0;

	while (size_x < 20)
	{
		y = (int)player->pos.y - 10;
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

int collision(t_player player, t_game *game, int mod)
{
	double x;
	double y;
	double px = player.pos.x;
	double py = player.pos.y;
	if (mod == 1)
	{
		x = ((px + 10) / 80);
		y = ((py) / 80);
	}
	else if (mod == 2)
	{
		x = ((px - 10) / 80) -0.001;
		y = ((py) / 80);
	}
	else if (mod == 3)
	{
		x = ((px) / 80);
		y = ((py + 10) / 80);
	}
	else if (mod == 4)
	{
		x = ((px) / 80);
		y = ((py - 10) / 80) - 0.001;
	}
	int ix = (int)floor(x);
	int iy = (int)floor(y);
	// printf("player: x: %f y: %f, index: x: %d y: %d\n", player.pos.x, player.pos.y, ix, iy);
	if (game->map[ix][iy] == 1)
		return(0);
	return (1);
}

void rotate_dir_plane(t_point *dir, t_point *plane, double speed, double l_r)
{
	double tmp_x;

	speed *= l_r;
	tmp_x = dir->x;
	dir->x = dir->x * cos(speed) - dir->y * sin(speed);
	dir->y = tmp_x * sin(speed) + dir->y * cos(speed);
	tmp_x = plane->x;
	plane->x = plane->x * cos(speed) - plane->y * sin(speed);
	plane->y = tmp_x * sin(speed) + plane->y * cos(speed);
}

void ft_hook(mlx_key_data_t keydata, void *param)
{
	t_game *game;

	game = (t_game*)param;

	if (keydata.key == MLX_KEY_W && (keydata.action == MLX_REPEAT || keydata.action == MLX_PRESS))
	{
		if (collision(game->player, game, 4))
			game->player.pos.y -= 5;
	}
	if (keydata.key == MLX_KEY_S && (keydata.action == MLX_REPEAT || keydata.action == MLX_PRESS))
	{
		if (collision(game->player, game, 3))
			game->player.pos.y += 5;
	}
	if (keydata.key == MLX_KEY_D && (keydata.action == MLX_REPEAT || keydata.action == MLX_PRESS))
	{
		if (collision(game->player, game, 1))
			game->player.pos.x += 5;
	}
	if (keydata.key == MLX_KEY_A && (keydata.action == MLX_REPEAT || keydata.action == MLX_PRESS))
	{
		if (collision(game->player, game, 2))
			game->player.pos.x -= 5;
	}
	if (keydata.key == MLX_KEY_Q && (keydata.action == MLX_REPEAT || keydata.action == MLX_PRESS))
		rotate_dir_plane(&game->player.dir, &game->player.scr, 0.1, -1);
	if (keydata.key == MLX_KEY_E && (keydata.action == MLX_REPEAT || keydata.action == MLX_PRESS))
		rotate_dir_plane(&game->player.dir, &game->player.scr, 0.1, 1);
}
//speed = how much rotation per call of function, l_r = left or right rotation; left -> l_r = 1, right -> l_r = -1;

void player_dir_line(t_game *game)
{
	t_point temp_dir;
	t_point temp_scr_start;
	t_point temp_scr_end;

	temp_dir.x = game->player.pos.x + game->player.dir.x;
	temp_dir.y = game->player.pos.y + game->player.dir.y;
	draw_line(&game->player.pos, &temp_dir, game);
	temp_scr_start.x = temp_dir.x - game->player.scr.x;
	temp_scr_start.y = temp_dir.y - game->player.scr.y;
	temp_scr_end.x = temp_dir.x + game->player.scr.x;
	temp_scr_end.y = temp_dir.y + game->player.scr.y;
	draw_line(&temp_scr_start, &temp_scr_end, game);
}

void render(void *param)
{
	t_game *game;

	game = (t_game*)param;
	grid(game);
	draw_player(game->img, &game->player);
	player_dir_line(game);

	mlx_image_to_window(game->mlx, game->img, 0, 0);
	usleep(1000);
}

int main(void)
{
	t_game game;

	game.player.pos.x = 120;
	game.player.pos.y = 120;
	game.player.height = HEIGHT;
	game.player.width = WIDTH;
	game.player.colour = 0x6cf542ff;
	game.color = 0xFFFF00FF;
	game.player.dir.x = 50;
	game.player.dir.y = 0;
	game.player.scr.x = 0;
	game.player.scr.y = 50;



	game.mlx = mlx_init(WIDTH, HEIGHT, "cub3d", true);
	
	game.img = mlx_new_image(game.mlx, WIDTH, HEIGHT);

	mlx_key_hook(game.mlx, &ft_hook, (void*)&game);
	mlx_loop_hook(game.mlx, render, (void*)&game);
	mlx_loop(game.mlx);
	mlx_terminate(game.mlx);
	return (0);
}
