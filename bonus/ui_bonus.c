/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_bonus.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pstrohal <pstrohal@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 14:09:47 by timschmi          #+#    #+#             */
/*   Updated: 2024/11/11 13:18:41 by pstrohal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub_bonus.h"

void	health_bar(t_game *game)
{
	int	start;
	int	end;
	int	hp;
	int	starty;
	int	y;
	int	x;

	start = WIDTH / 2 - 250;
	end = WIDTH / 2 + 250;
	hp = start + game->player.hp * 5;
	starty = HEIGHT - HEIGHT / 15;
	y = starty;
	while (y <= starty + 15)
	{
		x = start;
		while (x <= end)
		{
			if (x < hp)
				mlx_put_pixel(game->hp, x, y, 0xFF0000FF);
			else
				mlx_put_pixel(game->hp, x, y, 0x00000000);
			x++;
		}
		y++;
	}
}

void	load_gun(t_game *game)
{
	mlx_texture_t	**gun;
	mlx_image_t		*gun_img;

	gun = (mlx_texture_t **)malloc(sizeof(mlx_texture_t *) * 4);
	gun[0] = mlx_load_png("include/textures/gunsprites/1.png");
	gun[1] = mlx_load_png("include/textures/gunsprites/2.png");
	gun[2] = mlx_load_png("include/textures/gunsprites/3.png");
	gun[3] = mlx_load_png("include/textures/gunsprites/4.png");
	gun_img = mlx_texture_to_image(game->mlx, gun[0]);
	game->player.gun = gun;
	game->player.gun_img = gun_img;
	mlx_image_to_window(game->mlx, gun_img, WIDTH - 600, HEIGHT - 500);
}

void	gun_anim(t_game *game, int frame)
{
	static int	i = 0;
	t_point a;
	t_point b;
	a.x = WIDTH / 2.0;
	a.y = HEIGHT / 2.0;
	b.x = 1450.0;
	b.y = 780.0;
	if (game->player.attack)
	{
		if (game->player.attack == 1)
			draw_line(&a, &b, game->img, EA);
		game->player.attack = 2;
	}
	else if (!game->player.attack)
		return ;
	if (frame % 2 == 0 && i < 4)
		i++;
	if (i <= 3)
	{
		mlx_delete_image(game->mlx, game->player.gun_img);
		game->player.gun_img = mlx_texture_to_image(game->mlx,
				game->player.gun[i]);
		mlx_image_to_window(game->mlx, game->player.gun_img, WIDTH - 600, HEIGHT
			- 500);
		return ;
	}
	mlx_delete_image(game->mlx, game->player.gun_img);
	game->player.gun_img = mlx_texture_to_image(game->mlx, game->player.gun[0]);
	mlx_image_to_window(game->mlx, game->player.gun_img, WIDTH - 600, HEIGHT
		- 500);
	i = 0;
	game->player.attack = 0;
}
