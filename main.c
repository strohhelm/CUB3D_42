/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: timschmi <timschmi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 13:36:56 by timschmi          #+#    #+#             */
/*   Updated: 2024/09/13 18:20:24 by timschmi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void grid(mlx_image_t *img)
{
	int x = 0;
	int y = 0;

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
						mlx_put_pixel(img, arr_x, arr_y, 0x000000FF);
					else if (arr[x][y] == 1)
						mlx_put_pixel(img, arr_x, arr_y, 0xD3D3D3FF);
					else
						mlx_put_pixel(img, arr_x, arr_y, 0x808080FF);
					arr_y++;
				}
				arr_x++;
			}
			y++;
		}
		x++;
	}
}

void draw_player(mlx_image_t *img, player_t *player)
{
	int x = 0 + (int)player->x_pos;
	int y = 0 + (int)player->y_pos;
	int size_x = 0;
	int size_y = 0;

	while (size_x < 20)
	{
		y = 0 + (int)player->y_pos;
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
	printf("pos:%f\n", player->y_pos);
}


void ft_hook(mlx_key_data_t keydata, void *param)
{
	player_t *player;

	player = (player_t*)param;

	if (keydata.key == MLX_KEY_W && (keydata.action == MLX_REPEAT || keydata.action == MLX_PRESS))
		player->y_pos -= 5;
	if (keydata.key == MLX_KEY_S && (keydata.action == MLX_REPEAT || keydata.action == MLX_PRESS))
		player->y_pos += 5;
	
	if (keydata.key == MLX_KEY_D && (keydata.action == MLX_REPEAT || keydata.action == MLX_PRESS))
		player->x_pos += 5;
	if (keydata.key == MLX_KEY_A && (keydata.action == MLX_REPEAT || keydata.action == MLX_PRESS))
		player->x_pos -= 5;
}

void render(void *param)
{
	player_t *player;

	player = (player_t*)param;
	grid(player->img);
	draw_player(player->img, player);
	mlx_image_to_window(player->mlx, player->img, 0, 0);
	usleep(1000);
}


int main(void)
{
	// mlx_t *mlx;
	// mlx_image_t *img;
	player_t player;

	player.x_pos = 120;
	player.y_pos = 120;

	player.mlx = mlx_init(WIDTH, HEIGHT, "cub3d", true);
	
	player.img = mlx_new_image(player.mlx, WIDTH, HEIGHT);

	mlx_key_hook(player.mlx, &ft_hook, (void*)&player);
	mlx_loop_hook(player.mlx, render, (void*)&player);
	mlx_loop(player.mlx);
	mlx_terminate(player.mlx);
	return (0);
}
